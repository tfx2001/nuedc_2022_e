#include "tmp275.h"

#include "hpm_i2c_drv.h"

#define BOARD_TMP_I2C_BASE HPM_I2C3

static const float TMP275_RES_LSB[4] = {
    TMP275_RES_9_BITS_LSB,
    TMP275_RES_10_BITS_LSB,
    TMP275_RES_11_BITS_LSB,
    TMP275_RES_12_BITS_LSB,
};

static bool read_reg(tmp275_reg_t reg, uint8_t *data, uint32_t size) {
    return !i2c_master_address_read(BOARD_TMP_I2C_BASE, TMP275_DEV_ADDR, &reg, 1, data, size);
}

static bool write_reg(tmp275_reg_t reg, uint8_t *data, uint32_t size) {
    return !i2c_master_address_write(BOARD_TMP_I2C_BASE, TMP275_DEV_ADDR, &reg, 1, data, size);
}

void tmp275_init(tmp275_t *handle, tmp275_config_t *config) {
    handle->res = config->resolution;
    write_reg(TMP275_REG_CONFIG, (uint8_t *)config, sizeof(tmp275_config_t));
}

float tmp275_read_temp(tmp275_t *handle) {
    uint16_t raw_data;

    read_reg(TMP275_REG_TEMP, (uint8_t *)&raw_data, 2);
    raw_data = __builtin_bswap16(raw_data);
    return (raw_data >> 4) * TMP275_RES_12_BITS_LSB;
}