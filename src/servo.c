#include "servo.h"

#include "board.h"
#include "hpm_pwm_drv.h"
#include "setting.h"

static uint32_t freq;
static uint32_t reload;

extern setting_t g_setting;

const uint8_t SERVO_PWM_CMP_INDEX[] = {0, 1};

void servo_init()
{
    pwm_config_t config;
    pwm_cmp_config_t cmp_config;

    init_pwm_pins(HPM_PWM3);

    freq = clock_get_frequency(clock_mot3);
    reload = freq / 1000 * 20 - 1;

    pwm_get_default_pwm_config(HPM_PWM3, &config);

    config.enable_output = true;
    config.dead_zone_in_half_cycle = 0;
    config.invert_output = true;

    pwm_set_reload(HPM_PWM3, 0, reload);
    pwm_set_start_count(HPM_PWM3, 0, 0);

    pwm_get_default_cmp_config(HPM_PWM3, &cmp_config);
    cmp_config.mode = pwm_cmp_mode_output_compare;
    cmp_config.cmp = reload / 40 * 3; // 1.5ms high level, 90 deg
    cmp_config.update_trigger = pwm_shadow_register_update_on_modify;

    pwm_setup_waveform(HPM_PWM3, 3, &config, 0, &cmp_config, 1);
    pwm_setup_waveform(HPM_PWM3, 7, &config, 1, &cmp_config, 1);

    pwm_start_counter(HPM_PWM3);
    pwm_issue_shadow_register_lock_event(HPM_PWM3);
}

void servo_set_deg(uint8_t n, float deg)
{
    if (n == 0)
    {
        deg += g_setting.servo_ver_offset + 90.0F;
    }
    else
    {
        deg += g_setting.servo_hor_offset + 90.0F;
    }

    uint32_t cmp = (reload + 1) / 40.0F + deg * ((reload + 1) / 10 / 180.0);

    if (deg >= 0 && deg <= 180)
    {
        pwm_update_raw_cmp_edge_aligned(HPM_PWM3, n, cmp);
    }
}
