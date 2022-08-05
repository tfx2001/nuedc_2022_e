// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: 2022_nuedc

#include "servo.h"
#include "setting.h"
#include "ui.h"

extern bool is_following;
extern setting_t g_setting;

extern void set_laser(uint8_t value);
extern void refresh_setting_label();

static lv_timer_t *measure_timer;

/**
 * @brief 停止测量
 *
 * @param e
 */
void stop_measure(lv_event_t *e)
{
    if (measure_timer)
    {
        lv_timer_del(measure_timer);
        measure_timer = NULL;
    }
}

/**
 * @brief 开始测量
 *
 * @param e
 */
void start_measure(lv_event_t *e)
{
    extern void measure_timer_db(lv_timer_t * timer);

    is_following = false;
    set_laser(false);
    if (measure_timer == NULL)
    {
        measure_timer = lv_timer_create(measure_timer_db, 100, NULL);
    }
}

/**
 * @brief 开始声速校准
 *
 * @param e
 */
void start_calib_sound_speed(lv_event_t *e)
{
    extern void calibrate_timer_cb(lv_timer_t * timer);

    lv_timer_create(calibrate_timer_cb, 100, NULL);
}

/**
 * @brief 停止跟随
 *
 * @param e
 */
void stop_follow(lv_event_t *e)
{
    stop_measure(NULL);

    set_laser(0);
}

/**
 * @brief 开始跟随
 *
 * @param e
 */
void start_follow(lv_event_t *e)
{
    is_following = true;
    extern void measure_timer_db(lv_timer_t * timer);

    if (measure_timer == NULL)
    {
        measure_timer = lv_timer_create(measure_timer_db, 100, NULL);
    }
}

/**
 * @brief 增加舵机水平角度偏移
 *
 * @param e
 */
void add_servo_hor_offset(lv_event_t *e)
{
    g_setting.servo_hor_offset++;

    servo_set_deg(1, 0);
    refresh_setting_label();
}

/**
 * @brief 减少舵机水平角度偏移
 *
 * @param e
 */
void sub_servo_hor_offset(lv_event_t *e)
{
    g_setting.servo_hor_offset--;

    servo_set_deg(1, 0);
    refresh_setting_label();
}

/**
 * @brief 增加舵机水平角度偏移
 *
 * @param e
 */
void add_servo_ver_offset(lv_event_t *e)
{
    g_setting.servo_ver_offset++;

    servo_set_deg(0, 0);
    refresh_setting_label();
}

/**
 * @brief 减少舵机垂直角度便宜
 *
 * @param e
 */
void sub_servo_ver_offset(lv_event_t *e)
{
    g_setting.servo_ver_offset--;

    servo_set_deg(0, 0);
    refresh_setting_label();
}

/**
 * @brief 保存设置
 *
 * @param e
 */
void save_setting(lv_event_t *e)
{
    setting_save(&g_setting);
}

/**
 * @brief 放弃更改
 *
 * @param e
 */
void discard_setting(lv_event_t *e)
{
    setting_read(&g_setting);
}

/**
 * @brief 设置界面加载
 *
 * @param e
 */
void setting_load(lv_event_t *e)
{
    refresh_setting_label();
    set_laser(1);
}

/**
 * @brief 设置界面退出
 *
 * @param e
 */
void setting_exit(lv_event_t *e)
{
    set_laser(0);
}
