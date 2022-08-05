// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: 2022_nuedc

#ifndef _2022_NUEDC_UI_H
#define _2022_NUEDC_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

extern lv_obj_t * ui_Home;
extern lv_obj_t * ui_measureScreenBtn;
extern lv_obj_t * ui_Image1;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_settingScreenBtn;
extern lv_obj_t * ui_Image2;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Label9;
extern lv_obj_t * ui_MeasureScreen;
extern lv_obj_t * ui_distanceLabel;
extern lv_obj_t * ui_angleLabel;
extern lv_obj_t * ui_startMeasureBtn;
extern lv_obj_t * ui_startMeasureBtnLabel;
extern lv_obj_t * ui_backHomeBtn;
extern lv_obj_t * ui_startFollowBtn;
extern lv_obj_t * ui_startFollowBtnLabel;
extern lv_obj_t * ui_Setting;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_Label5;
extern lv_obj_t * ui_servoHorOffsetLabel;
extern lv_obj_t * ui_servoHorAddBtn;
extern lv_obj_t * ui_settingSaveBtn;
extern lv_obj_t * ui_Label6;
extern lv_obj_t * ui_Button6;
extern lv_obj_t * ui_Label7;
extern lv_obj_t * ui_startCaliBtn;
extern lv_obj_t * ui_Label8;
extern lv_obj_t * ui_servoVerSubBtn;
extern lv_obj_t * ui_servoVerOffsetLabel;
extern lv_obj_t * ui_servoHorSubBtn;
extern lv_obj_t * ui_servoVerAddBtn;
extern lv_obj_t * ui_soundSpeedLabel;

void stop_measure(lv_event_t * e);
void stop_measure(lv_event_t * e);
void start_measure(lv_event_t * e);
void stop_follow(lv_event_t * e);
void start_follow(lv_event_t * e);
void setting_load(lv_event_t * e);
void setting_exit(lv_event_t * e);
void add_servo_hor_offset(lv_event_t * e);
void save_setting(lv_event_t * e);
void discard_setting(lv_event_t * e);
void start_calib_sound_speed(lv_event_t * e);
void sub_servo_ver_offset(lv_event_t * e);
void sub_servo_hor_offset(lv_event_t * e);
void add_servo_ver_offset(lv_event_t * e);

LV_IMG_DECLARE(ui_img_2133783836);    // assets\icon-measure.png
LV_IMG_DECLARE(ui_img_488394416);    // assets\icon-setting.png
LV_IMG_DECLARE(ui_img_1071146721);    // assets\icon-back.png
LV_IMG_DECLARE(ui_img_565378741);    // assets\icon-add.png
LV_IMG_DECLARE(ui_img_145325322);    // assets\icon-sub.png


LV_FONT_DECLARE(ui_font_Font1);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
