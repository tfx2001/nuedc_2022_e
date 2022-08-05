#include "setting.h"

#include <stdio.h>

#include "board.h"
#include "hpm_romapi.h"

static xpi_nor_config_t s_xpi_nor_config;

static const uint32_t SETTING_FLASH_ADDRESS = 4 * 1024 * 1024; // start from 4MB
static const setting_t DEFAULT_SETTING = {
    .magic_number = SETTING_MAGIC_NUMBER,
    .servo_hor_offset = 0,
    .servo_ver_offset = 0,
    .sound_speed = 380,
};

setting_t setting_init(void)
{
    setting_t data;

    xpi_nor_config_option_t option;
    option.header.U = BOARD_APP_XPI_NOR_CFG_OPT_HDR;
    option.option0.U = BOARD_APP_XPI_NOR_CFG_OPT_OPT0;
    option.option1.U = BOARD_APP_XPI_NOR_CFG_OPT_OPT1;

    hpm_stat_t status;

    status = rom_xpi_nor_auto_config(BOARD_APP_XPI_NOR_XPI_BASE, &s_xpi_nor_config, &option);
    if (status != status_success)
    {
        printf("rom api init failed!\n");
        while (1);
    }

    status = rom_xpi_nor_read(BOARD_APP_XPI_NOR_XPI_BASE,
                              xpi_xfer_channel_auto,
                              &s_xpi_nor_config,
                              (uint32_t *)&data, SETTING_FLASH_ADDRESS,
                              sizeof(setting_t));

    if (status != status_success)
    {
        printf("setting read failed!\n");
        while (1)
            ;
    }

    if (data.magic_number != SETTING_MAGIC_NUMBER)
    {
        printf("find error magic number, init setting in flash.\n");
        data = DEFAULT_SETTING;
        setting_save(&data);
    }
    else
    {
        printf("successfully read setting from flash.\n\n");
    }

    return data;
}

bool setting_save(const setting_t *data)
{
    if (data->magic_number != SETTING_MAGIC_NUMBER)
    {
        return false;
    }

    disable_global_irq(CSR_MSTATUS_MIE_MASK);

    rom_xpi_nor_erase_block(BOARD_APP_XPI_NOR_XPI_BASE, xpi_xfer_channel_auto, &s_xpi_nor_config,
                            SETTING_FLASH_ADDRESS);
    rom_xpi_nor_program(BOARD_APP_XPI_NOR_XPI_BASE, xpi_xfer_channel_auto, &s_xpi_nor_config,
                        (uint32_t *)data, SETTING_FLASH_ADDRESS, sizeof(setting_t));

    enable_global_irq(CSR_MSTATUS_MIE_MASK);

    return true;
}

void setting_read(setting_t *data)
{
    rom_xpi_nor_read(BOARD_APP_XPI_NOR_XPI_BASE,
                     xpi_xfer_channel_auto,
                     &s_xpi_nor_config,
                     (uint32_t *)data, SETTING_FLASH_ADDRESS,
                     sizeof(setting_t));
}
