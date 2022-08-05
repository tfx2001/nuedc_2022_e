#include "ns2009.h"

#include "board.h"
#include "hpm_gpio_drv.h"
#include "hpm_i2c_drv.h"

#define X_MIN 2300.0F
#define X_MAX 62980.0F
#define Y_MIN 3330.0F
#define Y_MAX 60670.0F

void ns2009_init()
{
    i2c_config_t config = {
        .i2c_mode = i2c_mode_fast,
        .is_10bit_addressing = false,
    };

    init_cap_pins();
    gpio_set_pin_input(BOARD_CAP_INTR_GPIO, BOARD_CAP_INTR_GPIO_INDEX, BOARD_CAP_INTR_GPIO_PIN);

    /* Init I2C0 */
    init_i2c_pins(BOARD_CAP_I2C_BASE);
    i2c_init_master(BOARD_CAP_I2C_BASE, 400000, &config);
}

bool ns2009_is_touch()
{
    return !gpio_read_pin(BOARD_CAP_INTR_GPIO, BOARD_CAP_INTR_GPIO_INDEX, BOARD_CAP_INTR_GPIO_PIN);
}

uint16_t ns2009_read_pos(ns2009_input_t input)
{
    ns2009_cmd_t cmd = {
        .input = input,
        .mode = NS2009_MODE_12B,
        .power_down = NS2009_POWER_DOWN_ENABLE,
        .reserve_b0 = 0,
        .reserve_b3 = 0,
    };
    uint8_t buf[2];
    uint16_t value;

    i2c_master_write(BOARD_CAP_I2C_BASE, NS2009_ADDR, (uint8_t *)&cmd, sizeof(cmd));
    i2c_master_read(BOARD_CAP_I2C_BASE, NS2009_ADDR, buf, 2);
    value = (buf[0] << 8) | (buf[1] >> 4);

    switch (input)
    {
    case InputX:
        return BOARD_LCD_WIDTH - BOARD_LCD_WIDTH / (X_MAX - X_MIN) * (value - X_MIN);
    case InputY:
        return BOARD_LCD_HEIGHT - BOARD_LCD_HEIGHT / (Y_MAX - Y_MIN) * (value - Y_MIN);
    }
}
