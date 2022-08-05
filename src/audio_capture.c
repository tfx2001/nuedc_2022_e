#include "audio_capture.h"

#include "board.h"
#include "hpm_adc12_drv.h"

#include "FreeRTOS.h"
#include "task.h"

#define MIC_ADC_BASE HPM_ADC1
#define MIC_ADC_CHANNEL_1 7
#define MIC_ADC_CHANNEL_2 8
#define MIC_ADC_CHANNEL_3 9
#define MIC_ADC_CHANNEL_4 10

static uint8_t mic_adc_channels[] = {
    MIC_ADC_CHANNEL_1,
    MIC_ADC_CHANNEL_2,
    MIC_ADC_CHANNEL_3,
    MIC_ADC_CHANNEL_4,
};

void audio_cap_init()
{
    adc12_config_t cfg;
    adc12_channel_config_t ch_cfg;

    board_init_adc12_pins();

    /* initialize an ADC instance */
    adc12_get_default_config(&cfg);

    cfg.res = adc12_res_12_bits;
    cfg.conv_mode = adc12_conv_mode_period;
    cfg.adc_clk_div = 1;
    cfg.sel_sync_ahb = true;
    cfg.adc_ahb_en = false;

    adc12_init(MIC_ADC_BASE, &cfg);
    MIC_ADC_BASE->BUF_CFG0 = ADC12_BUF_CFG0_WAIT_DIS_SET(1);

    /* initialize an ADC channel */
    adc12_get_channel_default_config(&ch_cfg);
    ch_cfg.diff_sel = adc12_sample_signal_single_ended;
    ch_cfg.sample_cycle = 20;
    for (int i = 0; i < 4; i++)
    {
        ch_cfg.ch = mic_adc_channels[i];
        adc12_init_channel(MIC_ADC_BASE, &ch_cfg);
    }

    /* init periodic sample mode */
    adc12_prd_config_t prd_config;
    prd_config.prescale = 5;
    prd_config.period_in_ms = 10;

    for (int i = 0; i < 4; i++)
    {
        prd_config.ch = mic_adc_channels[i];
        adc12_set_prd_config(MIC_ADC_BASE, &prd_config);
    }
}

void audio_get_value(float *data, uint32_t count, uint8_t *channel_seq, uint8_t channel_count)
{
    /* enter critical */
    vTaskSuspendAll();

    uint16_t result;

    for (uint32_t i = 0; i < count; i++)
    {
        for (uint8_t j = 0; j < channel_count; j++)
        {
            adc12_get_prd_result(MIC_ADC_BASE, channel_seq[j], &result);
            *(data + j * count + i) = (float)((result >> 4) & ((1 << 12) - 1));
        }
        clock_cpu_delay_us(10);
    }

    /* exit critial */
    xTaskResumeAll();
}
