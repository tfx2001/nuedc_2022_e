#include "lv_port.h"

#include "board.h"
#include "hpm_dma_drv.h"
#include "hpm_l1c_drv.h"
#include "hpm_lcdc_drv.h"

#include "lvgl.h"
#include "ns2009.h"

#define LCD_WIDTH 480
#define LCD_HEIGHT 272

#define LCD_CONTROLLER BOARD_LCD_BASE
#define LCD_LAYER_INDEX (0)
#define LCD_LAYER_DONE_MASK (LCD_LAYER_INDEX + 1)
#define LCD_IRQ_NUM BOARD_LCD_IRQ

static lcdc_layer_config_t layer;
static lv_color_t buf1[LCD_HEIGHT * LCD_WIDTH] ATTR_PLACE_AT(".framebuffer");
static lv_color_t buf2[LCD_HEIGHT * LCD_WIDTH] ATTR_PLACE_AT(".framebuffer");
static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;

void isr_lcd(void)
{
    volatile uint32_t s = lcdc_get_dma_status(LCD_CONTROLLER);
    lcdc_clear_dma_status(LCD_CONTROLLER, s);
    if (s & (LCD_LAYER_DONE_MASK << LCDC_DMA_ST_DMA0_DONE_SHIFT))
    {
        if (lcdc_layer_control_shadow_loaded(LCD_CONTROLLER, 0))
        {
            lv_disp_flush_ready(&disp_drv);
        }
    }
}
SDK_DECLARE_EXT_ISR_M(LCD_IRQ_NUM, isr_lcd)

/* Initialize your display and the required peripherals. */
static void init_lcd(void)
{
    display_pixel_format_t pixel_format;
    lcdc_config_t config = {0};
    lcdc_get_default_config(LCD_CONTROLLER, &config);

    config.resolution_x = LCD_WIDTH;
    config.resolution_y = LCD_HEIGHT;

#if LV_COLOR_DEPTH == 32
    pixel_format = display_pixel_format_argb8888;
#elif LV_COLOR_DEPTH == 16
    pixel_format = display_pixel_format_rgb565;
#else
#error only support 16 or 32 color depth
#endif

    lcdc_init(LCD_CONTROLLER, &config);
    lcdc_get_default_layer_config(LCD_CONTROLLER, &layer, pixel_format, LCD_LAYER_INDEX);

    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));

    layer.position_x = 0;
    layer.position_y = 0;
    layer.width = config.resolution_x;
    layer.height = config.resolution_y;
    layer.buffer = (uint32_t)core_local_mem_to_sys_address(HPM_CORE0, (uint32_t)buf1);
    layer.background.u = 0;

    if (status_success != lcdc_config_layer(LCD_CONTROLLER, LCD_LAYER_INDEX, &layer, true))
    {
        printf("failed to configure layer\n");
        while (1)
            ;
    }

    lcdc_turn_on_display(LCD_CONTROLLER);
    lcdc_enable_interrupt(LCD_CONTROLLER, LCD_LAYER_DONE_MASK << 16);
    intc_m_enable_irq_with_priority(LCD_IRQ_NUM, 1);
}

static void lv_flush_cb(struct _lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t buffer = core_local_mem_to_sys_address(HPM_CORE0, (uint32_t)color_p);
    if (l1c_dc_is_enabled())
    {
        uint32_t aligned_start = HPM_L1C_CACHELINE_ALIGN_DOWN((uint32_t)buffer);
        uint32_t aligned_end = HPM_L1C_CACHELINE_ALIGN_UP((uint32_t)buffer + LCD_HEIGHT * LCD_WIDTH * LV_COLOR_DEPTH / 8);
        uint32_t aligned_size = aligned_end - aligned_start;
        l1c_dc_writeback(aligned_start, aligned_size);
    }
    lcdc_layer_set_next_buffer(LCD_CONTROLLER, LCD_LAYER_INDEX, buffer);
}

static void lv_indev_read_cb(struct _lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    data->state = ns2009_is_touch();

    if (data->state)
    {
        data->point.x = ns2009_read_pos(InputX);
        data->point.y = ns2009_read_pos(InputY);
    }
}

void lv_init_disp_driver()
{
    board_init_lcd();
    init_lcd();

    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, LCD_HEIGHT * LCD_WIDTH);
    lv_disp_drv_init(&disp_drv);

    disp_drv.draw_buf = &draw_buf;
    disp_drv.full_refresh = true;
    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HEIGHT;
    disp_drv.flush_cb = lv_flush_cb;
    lv_disp_drv_register(&disp_drv);
}

void lv_init_indev_driver()
{
    ns2009_init();

    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = lv_indev_read_cb;
    lv_indev_drv_register(&indev_drv);
}
