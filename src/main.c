#include "main.h"

#include <math.h>
#include <stdio.h>

#include "board.h"
#include "hpm_debug_console.h"
#include "hpm_gpio_drv.h"
#include "hpm_math.h"

#include "FreeRTOS.h"
#include "task.h"

#include "lv_port.h"
#include "lvgl.h"
#include "ui.h"

#include "audio_capture.h"
#include "servo.h"
#include "setting.h"

#define DATA_LENGTH 2000
#define CHANNEL_COUNT 3

static float32_t mic_data[CHANNEL_COUNT][DATA_LENGTH];
static float32_t mic_data_corr[DATA_LENGTH * 2];
static const uint8_t CHANNEL_SEQ[] = {8, 7, 10};

static float distance_result[10];
static float angle_result[10];

bool is_following;
setting_t g_setting;

/**
 * @brief 计算相对时延
 *
 * @param index 数组索引
 * @return double 信号时延（单位：s）
 */
static inline double get_latency(uint32_t index)
{
    return ((int)index - 2000) / 100000.0;
}

/**
 * @brief 计算声源角度
 *
 * @param index 数组索引
 * @param cm 麦克风间距
 * @return float 角度（单位：deg）
 */
static inline float get_angle(uint32_t index, int32_t cm)
{
    return acosf(g_setting.sound_speed * ((int)index - 2000) / (cm * 1000.0F)) * 57.3F - 90;
}

/**
 * @brief 平方函数
 *
 * @param x
 * @return double
 */
static inline double square(double x) { return (x * x); }

/**
 * @brief 设置激光笔状态
 *
 * @param value 要设置的值
 */
void set_laser(uint8_t value)
{
    gpio_write_pin(HPM_GPIO0, GPIO_DI_GPIOB, 26, value);
}

/**
 * @brief 更新设置界面标签
 *
 */
void refresh_setting_label()
{
    lv_label_set_text_fmt(ui_servoHorOffsetLabel, "%d°", g_setting.servo_hor_offset);
    lv_label_set_text_fmt(ui_servoVerOffsetLabel, "%d°", g_setting.servo_ver_offset);
    lv_label_set_text_fmt(ui_soundSpeedLabel, "%d m/s", g_setting.sound_speed);
}

/**
 * @brief 对信号进行采样并归一化
 *
 */
static void sample_data()
{
    /* get audio data */
    audio_get_value(mic_data, DATA_LENGTH, CHANNEL_SEQ, CHANNEL_COUNT);

    /* filter DC component */
    float32_t dc_component;
    for (int i = 0; i < CHANNEL_COUNT; i++)
    {
        dc_component = hpm_dsp_mean_f32(mic_data[i], DATA_LENGTH);
        for (int j = 0; j < DATA_LENGTH; j++)
            mic_data[i][j] -= dc_component;
    }

    /* normalized */
    float32_t max_value, min_value;

    for (int i = 0; i < CHANNEL_COUNT; i++)
    {
        max_value = hpm_dsp_max_f32(mic_data[i], DATA_LENGTH, NULL);
        min_value = hpm_dsp_min_f32(mic_data[i], DATA_LENGTH, NULL);
        for (int j = 0; j < DATA_LENGTH; j++)
        {
            mic_data[i][j] = (mic_data[i][j] - min_value) * 2 / (max_value - min_value) - 1;
        }
    }
}

/**
 * @brief 测量定时器回调函数
 *
 * @param timer 定时器的指针
 */
void measure_timer_db(lv_timer_t *timer)
{
    sample_data();

    /* corss correlate */
    uint32_t max_value_index[4];
    float max_value;

    hpm_dsp_corr_f32(mic_data[0], DATA_LENGTH, mic_data[1], DATA_LENGTH, mic_data_corr);
    max_value = hpm_dsp_max_f32(mic_data_corr, DATA_LENGTH * 2 - 1, max_value_index + 0);
    hpm_dsp_corr_f32(mic_data[0], DATA_LENGTH, mic_data[2], DATA_LENGTH, mic_data_corr);
    hpm_dsp_max_f32(mic_data_corr, DATA_LENGTH * 2 - 1, max_value_index + 2);
    hpm_dsp_corr_f32(mic_data[1], DATA_LENGTH, mic_data[2], DATA_LENGTH, mic_data_corr);
    hpm_dsp_max_f32(mic_data_corr, DATA_LENGTH * 2 - 1, max_value_index + 3);

    /* calculate angle and distance */
    float angle = get_angle(max_value_index[0], 80);
    double a = square(g_setting.sound_speed) * (square(get_latency(max_value_index[2])) + square(get_latency(max_value_index[3])));
    double b = g_setting.sound_speed * (get_latency(max_value_index[2]) + get_latency(max_value_index[3]));
    double distance = fabs(2 * square(0.4) - a) /
                      fabs(2 * b);

    /* refresh UI and debounce */
    static int debounce_count = 0;
    uint32_t *measure_count = (uint32_t *)&timer->user_data;
    if (max_value >= 100 && debounce_count++ >= 5)
    {
        /* 是否为跟随模式 */
        if (is_following)
        {
            lv_label_set_text_fmt(ui_angleLabel, "角度：%d.%02d°", (int)angle, abs((int)(angle * 100) % 100));
            lv_label_set_text_fmt(ui_distanceLabel, "距离：%dcm", (int)(distance * 100));
            servo_set_deg(1, angle);
            set_laser(true);
        }
        else
        {
            angle_result[*measure_count] = angle;
            distance_result[*measure_count] = distance;
            *measure_count = *measure_count + 1;
        }
        /* 对测量结果取平均值 */
        if (*measure_count == 5)
        {
            distance = hpm_dsp_mean_f32(distance_result, 5);
            angle = hpm_dsp_mean_f32(angle_result, 5);

            lv_label_set_text_fmt(ui_angleLabel, "角度：%d.%02d°", (int)angle, abs((int)(angle * 100) % 100));
            lv_label_set_text_fmt(ui_distanceLabel, "距离：%dcm", (int)(distance * 100));

            servo_set_deg(1, angle);
            set_laser(true);
            /* 停止测量 */
            lv_obj_clear_state(ui_startMeasureBtn, LV_STATE_CHECKED);
            lv_event_send(ui_startMeasureBtn, LV_EVENT_VALUE_CHANGED, NULL);
        }
    }
    else if (max_value < 100)
    {
        debounce_count = 0;
        *measure_count = 0;
    }
}

/**
 * @brief 声速校准定时器回调函数
 *
 * @param timer 定时器指针
 */
void calibrate_timer_cb(lv_timer_t *timer)
{
    sample_data();

    /* corss correlate */
    int32_t max_value_index[4];

    hpm_dsp_corr_f32(mic_data[0], DATA_LENGTH, mic_data[1], DATA_LENGTH, mic_data_corr);
    hpm_dsp_max_f32(mic_data_corr, DATA_LENGTH * 2 - 1, max_value_index + 0);
    hpm_dsp_corr_f32(mic_data[0], DATA_LENGTH, mic_data[2], DATA_LENGTH, mic_data_corr);
    hpm_dsp_max_f32(mic_data_corr, DATA_LENGTH * 2 - 1, max_value_index + 1);
    hpm_dsp_corr_f32(mic_data[1], DATA_LENGTH, mic_data[2], DATA_LENGTH, mic_data_corr);
    hpm_dsp_max_f32(mic_data_corr, DATA_LENGTH * 2 - 1, max_value_index + 2);

    for (int i = 0; i < 3; i++)
        max_value_index[i] = max_value_index[i] - 2000;

    max_value_index[0] = max_value_index[0] / 2;

    float max_value = 0, min_value = 9999;
    for (int i = 0; i < 3; i++)
    {
        max_value = fmax(max_value, fabs(max_value_index[i]));
        min_value = fmin(min_value, fabs(max_value_index[i]));
    }
    if (max_value - min_value <= 5.0F)
    {
        g_setting.sound_speed = 0.4 / get_latency((max_value + min_value) / 2 + 2000);
        refresh_setting_label();
        lv_timer_del(timer);
        lv_obj_clear_state(ui_startCaliBtn, LV_STATE_DISABLED);
    }
}

static void lvgl_task_entry(void *param)
{
    lv_init();
    lv_init_disp_driver();
    lv_init_indev_driver();

    ui_init();

    while (true)
    {
        lv_timer_handler();
        vTaskDelay(15);
    }
}

int main(void)
{

    board_init();

    board_init_led_pins();
    audio_cap_init();
    g_setting = setting_init();
    servo_init();

    board_delay_ms(100);
    servo_set_deg(0, 0);
    servo_set_deg(1, 0);

    /* init laser pin */
    HPM_IOC->PAD[IOC_PAD_PB26].FUNC_CTL = IOC_PB26_FUNC_CTL_GPIO_B_26;
    gpio_set_pin_output_with_initial(HPM_GPIO0, GPIO_DI_GPIOB, 26, false);

    if (xTaskCreate(lvgl_task_entry, "lvgl", 2048, NULL, 4, NULL) != pdPASS)
    {
        printf("task LVGL creation failed!.\n");
        while (1)
            ;
    }

    vTaskStartScheduler();

    while (1)
        ;
    return 0;
}

void vApplicationTickHook(void)
{
    lv_tick_inc(1);
}

void vApplicationStackOverflowHook(TaskHandle_t xTask,
                                   char *pcTaskName)
{
    printf("fatal: task %s stack overflow detected\n", pcTaskName);
    while (1)
        ;
}
