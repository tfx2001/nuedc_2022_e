// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: 2022_nuedc

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Home;
lv_obj_t * ui_measureScreenBtn;
lv_obj_t * ui_Image1;
lv_obj_t * ui_Label1;
lv_obj_t * ui_settingScreenBtn;
lv_obj_t * ui_Image2;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label9;
lv_obj_t * ui_MeasureScreen;
lv_obj_t * ui_distanceLabel;
lv_obj_t * ui_angleLabel;
lv_obj_t * ui_startMeasureBtn;
lv_obj_t * ui_startMeasureBtnLabel;
lv_obj_t * ui_backHomeBtn;
lv_obj_t * ui_startFollowBtn;
lv_obj_t * ui_startFollowBtnLabel;
lv_obj_t * ui_Setting;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Label4;
lv_obj_t * ui_Label5;
lv_obj_t * ui_servoHorOffsetLabel;
lv_obj_t * ui_servoHorAddBtn;
lv_obj_t * ui_settingSaveBtn;
lv_obj_t * ui_Label6;
lv_obj_t * ui_Button6;
lv_obj_t * ui_Label7;
lv_obj_t * ui_startCaliBtn;
lv_obj_t * ui_Label8;
lv_obj_t * ui_servoVerSubBtn;
lv_obj_t * ui_servoVerOffsetLabel;
lv_obj_t * ui_servoHorSubBtn;
lv_obj_t * ui_servoVerAddBtn;
lv_obj_t * ui_soundSpeedLabel;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
static void ui_event_Home(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Setting, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
    }
}
static void ui_event_measureScreenBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_MeasureScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
    }
}
static void ui_event_settingScreenBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Setting, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
    }
}
static void ui_event_MeasureScreen(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_SCREEN_UNLOAD_START) {
        stop_measure(e);
    }
}
static void ui_event_startMeasureBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        _ui_label_set_property(ui_startMeasureBtnLabel, _UI_LABEL_PROPERTY_TEXT, "开始测量");
        stop_measure(e);
    }
    if(event == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        _ui_label_set_property(ui_startMeasureBtnLabel, _UI_LABEL_PROPERTY_TEXT, "停止测量");
        start_measure(e);
    }
}
static void ui_event_backHomeBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Home, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
    }
}
static void ui_event_startFollowBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        _ui_label_set_property(ui_startFollowBtnLabel, _UI_LABEL_PROPERTY_TEXT, "开始跟随");
        stop_follow(e);
    }
    if(event == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        _ui_label_set_property(ui_startFollowBtnLabel, _UI_LABEL_PROPERTY_TEXT, "停止跟随");
        start_follow(e);
    }
}
static void ui_event_Setting(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_SCREEN_LOAD_START) {
        setting_load(e);
    }
    if(event == LV_EVENT_SCREEN_UNLOAD_START) {
        setting_exit(e);
    }
}
static void ui_event_servoHorAddBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        add_servo_hor_offset(e);
        (e);
    }
}
static void ui_event_settingSaveBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        save_setting(e);
        _ui_screen_change(ui_Home, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
    }
}
static void ui_event_Button6(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Home, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
        discard_setting(e);
    }
}
static void ui_event_startCaliBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        start_calib_sound_speed(e);
        _ui_state_modify(ui_startCaliBtn, LV_STATE_DISABLED, _UI_MODIFY_STATE_ADD);
    }
}
static void ui_event_servoVerSubBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        sub_servo_ver_offset(e);
    }
}
static void ui_event_servoHorSubBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        sub_servo_hor_offset(e);
    }
}
static void ui_event_servoVerAddBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        add_servo_ver_offset(e);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Home_screen_init(void)
{

    // ui_Home

    ui_Home = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Home, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Home, ui_event_Home, LV_EVENT_ALL, NULL);

    // ui_measureScreenBtn

    ui_measureScreenBtn = lv_btn_create(ui_Home);

    lv_obj_set_width(ui_measureScreenBtn, 128);
    lv_obj_set_height(ui_measureScreenBtn, 128);

    lv_obj_set_x(ui_measureScreenBtn, -84);
    lv_obj_set_y(ui_measureScreenBtn, 24);

    lv_obj_set_align(ui_measureScreenBtn, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_measureScreenBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_measureScreenBtn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_measureScreenBtn, ui_event_measureScreenBtn, LV_EVENT_ALL, NULL);

    // ui_Image1

    ui_Image1 = lv_img_create(ui_measureScreenBtn);
    lv_img_set_src(ui_Image1, &ui_img_2133783836);

    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image1, 12);
    lv_obj_set_y(ui_Image1, -8);

    lv_obj_set_align(ui_Image1, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Label1

    ui_Label1 = lv_label_create(ui_measureScreenBtn);

    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label1, 8);
    lv_obj_set_y(ui_Label1, 2);

    lv_obj_set_align(ui_Label1, LV_ALIGN_BOTTOM_RIGHT);

    lv_label_set_text(ui_Label1, "Measure 测量");

    lv_obj_set_style_text_font(ui_Label1, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_settingScreenBtn

    ui_settingScreenBtn = lv_btn_create(ui_Home);

    lv_obj_set_width(ui_settingScreenBtn, 128);
    lv_obj_set_height(ui_settingScreenBtn, 128);

    lv_obj_set_x(ui_settingScreenBtn, 84);
    lv_obj_set_y(ui_settingScreenBtn, 24);

    lv_obj_set_align(ui_settingScreenBtn, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_settingScreenBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_settingScreenBtn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_settingScreenBtn, ui_event_settingScreenBtn, LV_EVENT_ALL, NULL);

    // ui_Image2

    ui_Image2 = lv_img_create(ui_settingScreenBtn);
    lv_img_set_src(ui_Image2, &ui_img_488394416);

    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image2, 12);
    lv_obj_set_y(ui_Image2, -8);

    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Label2

    ui_Label2 = lv_label_create(ui_settingScreenBtn);

    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label2, 8);
    lv_obj_set_y(ui_Label2, 2);

    lv_obj_set_align(ui_Label2, LV_ALIGN_BOTTOM_RIGHT);

    lv_label_set_text(ui_Label2, "Setting 设置");

    lv_obj_set_style_text_font(ui_Label2, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label9

    ui_Label9 = lv_label_create(ui_Home);

    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label9, 0);
    lv_obj_set_y(ui_Label9, 32);

    lv_obj_set_align(ui_Label9, LV_ALIGN_TOP_MID);

    lv_label_set_text(ui_Label9, "声源定位跟踪系统");

    lv_obj_set_style_text_align(ui_Label9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label9, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_MeasureScreen_screen_init(void)
{

    // ui_MeasureScreen

    ui_MeasureScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_MeasureScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_MeasureScreen, ui_event_MeasureScreen, LV_EVENT_ALL, NULL);

    // ui_distanceLabel

    ui_distanceLabel = lv_label_create(ui_MeasureScreen);

    lv_obj_set_width(ui_distanceLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_distanceLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_distanceLabel, 0);
    lv_obj_set_y(ui_distanceLabel, -24);

    lv_obj_set_align(ui_distanceLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_distanceLabel, "");

    lv_obj_set_style_text_align(ui_distanceLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_distanceLabel, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_angleLabel

    ui_angleLabel = lv_label_create(ui_MeasureScreen);

    lv_obj_set_width(ui_angleLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_angleLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_angleLabel, 0);
    lv_obj_set_y(ui_angleLabel, 0);

    lv_obj_set_align(ui_angleLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_angleLabel, "");

    lv_obj_set_style_text_align(ui_angleLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_angleLabel, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_startMeasureBtn

    ui_startMeasureBtn = lv_btn_create(ui_MeasureScreen);

    lv_obj_set_width(ui_startMeasureBtn, 100);
    lv_obj_set_height(ui_startMeasureBtn, 50);

    lv_obj_set_x(ui_startMeasureBtn, -64);
    lv_obj_set_y(ui_startMeasureBtn, 89);

    lv_obj_set_align(ui_startMeasureBtn, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_startMeasureBtn, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_startMeasureBtn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_startMeasureBtn, ui_event_startMeasureBtn, LV_EVENT_ALL, NULL);

    // ui_startMeasureBtnLabel

    ui_startMeasureBtnLabel = lv_label_create(ui_startMeasureBtn);

    lv_obj_set_width(ui_startMeasureBtnLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_startMeasureBtnLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_startMeasureBtnLabel, 0);
    lv_obj_set_y(ui_startMeasureBtnLabel, 0);

    lv_obj_set_align(ui_startMeasureBtnLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_startMeasureBtnLabel, "开始测量");

    lv_obj_set_style_text_font(ui_startMeasureBtnLabel, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_backHomeBtn

    ui_backHomeBtn = lv_imgbtn_create(ui_MeasureScreen);
    lv_imgbtn_set_src(ui_backHomeBtn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_1071146721, NULL);
    lv_imgbtn_set_src(ui_backHomeBtn, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_1071146721, NULL);

    lv_obj_set_width(ui_backHomeBtn, 32);
    lv_obj_set_height(ui_backHomeBtn, 32);

    lv_obj_set_x(ui_backHomeBtn, 9);
    lv_obj_set_y(ui_backHomeBtn, 9);

    lv_obj_add_event_cb(ui_backHomeBtn, ui_event_backHomeBtn, LV_EVENT_ALL, NULL);

    // ui_startFollowBtn

    ui_startFollowBtn = lv_btn_create(ui_MeasureScreen);

    lv_obj_set_width(ui_startFollowBtn, 100);
    lv_obj_set_height(ui_startFollowBtn, 50);

    lv_obj_set_x(ui_startFollowBtn, 64);
    lv_obj_set_y(ui_startFollowBtn, 89);

    lv_obj_set_align(ui_startFollowBtn, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_startFollowBtn, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_startFollowBtn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_startFollowBtn, ui_event_startFollowBtn, LV_EVENT_ALL, NULL);

    // ui_startFollowBtnLabel

    ui_startFollowBtnLabel = lv_label_create(ui_startFollowBtn);

    lv_obj_set_width(ui_startFollowBtnLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_startFollowBtnLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_startFollowBtnLabel, 0);
    lv_obj_set_y(ui_startFollowBtnLabel, 0);

    lv_obj_set_align(ui_startFollowBtnLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_startFollowBtnLabel, "开始跟随");

    lv_obj_set_style_text_font(ui_startFollowBtnLabel, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_Setting_screen_init(void)
{

    // ui_Setting

    ui_Setting = lv_obj_create(NULL);

    lv_obj_add_event_cb(ui_Setting, ui_event_Setting, LV_EVENT_ALL, NULL);

    // ui_Label3

    ui_Label3 = lv_label_create(ui_Setting);

    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label3, 12);
    lv_obj_set_y(ui_Label3, 24);

    lv_label_set_text(ui_Label3, "舵机水平角偏移");

    lv_obj_set_style_text_font(ui_Label3, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label4

    ui_Label4 = lv_label_create(ui_Setting);

    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label4, 12);
    lv_obj_set_y(ui_Label4, 56);

    lv_label_set_text(ui_Label4, "舵机垂直角偏移");

    lv_obj_set_style_text_font(ui_Label4, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label5

    ui_Label5 = lv_label_create(ui_Setting);

    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label5, 12);
    lv_obj_set_y(ui_Label5, 104);

    lv_label_set_text(ui_Label5, "声速校准");

    lv_obj_set_style_text_font(ui_Label5, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_servoHorOffsetLabel

    ui_servoHorOffsetLabel = lv_label_create(ui_Setting);

    lv_obj_set_width(ui_servoHorOffsetLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_servoHorOffsetLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_servoHorOffsetLabel, 152);
    lv_obj_set_y(ui_servoHorOffsetLabel, 24);

    lv_label_set_text(ui_servoHorOffsetLabel, "0 °");

    lv_obj_set_style_text_font(ui_servoHorOffsetLabel, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_servoHorAddBtn

    ui_servoHorAddBtn = lv_imgbtn_create(ui_Setting);
    lv_imgbtn_set_src(ui_servoHorAddBtn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_565378741, NULL);
    lv_imgbtn_set_src(ui_servoHorAddBtn, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_565378741, NULL);

    lv_obj_set_height(ui_servoHorAddBtn, 24);
    lv_obj_set_width(ui_servoHorAddBtn, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_servoHorAddBtn, 440);
    lv_obj_set_y(ui_servoHorAddBtn, 18);

    lv_obj_add_event_cb(ui_servoHorAddBtn, ui_event_servoHorAddBtn, LV_EVENT_ALL, NULL);

    // ui_settingSaveBtn

    ui_settingSaveBtn = lv_btn_create(ui_Setting);

    lv_obj_set_width(ui_settingSaveBtn, 100);
    lv_obj_set_height(ui_settingSaveBtn, 50);

    lv_obj_set_x(ui_settingSaveBtn, 64);
    lv_obj_set_y(ui_settingSaveBtn, -12);

    lv_obj_set_align(ui_settingSaveBtn, LV_ALIGN_BOTTOM_MID);

    lv_obj_add_flag(ui_settingSaveBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_settingSaveBtn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_settingSaveBtn, ui_event_settingSaveBtn, LV_EVENT_ALL, NULL);

    // ui_Label6

    ui_Label6 = lv_label_create(ui_settingSaveBtn);

    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label6, 0);
    lv_obj_set_y(ui_Label6, 0);

    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label6, "保存");

    lv_obj_set_style_text_font(ui_Label6, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Button6

    ui_Button6 = lv_btn_create(ui_Setting);

    lv_obj_set_width(ui_Button6, 100);
    lv_obj_set_height(ui_Button6, 50);

    lv_obj_set_x(ui_Button6, -64);
    lv_obj_set_y(ui_Button6, -12);

    lv_obj_set_align(ui_Button6, LV_ALIGN_BOTTOM_MID);

    lv_obj_add_flag(ui_Button6, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button6, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Button6, ui_event_Button6, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_Button6, lv_color_hex(0xF64031), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label7

    ui_Label7 = lv_label_create(ui_Button6);

    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label7, 0);
    lv_obj_set_y(ui_Label7, 0);

    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label7, "放弃");

    lv_obj_set_style_text_font(ui_Label7, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_startCaliBtn

    ui_startCaliBtn = lv_btn_create(ui_Setting);

    lv_obj_set_width(ui_startCaliBtn, 100);
    lv_obj_set_height(ui_startCaliBtn, 50);

    lv_obj_set_x(ui_startCaliBtn, 368);
    lv_obj_set_y(ui_startCaliBtn, 88);

    lv_obj_add_flag(ui_startCaliBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_startCaliBtn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_startCaliBtn, ui_event_startCaliBtn, LV_EVENT_ALL, NULL);

    // ui_Label8

    ui_Label8 = lv_label_create(ui_startCaliBtn);

    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label8, 0);
    lv_obj_set_y(ui_Label8, 0);

    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label8, "开始校准");

    lv_obj_set_style_text_font(ui_Label8, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_servoVerSubBtn

    ui_servoVerSubBtn = lv_imgbtn_create(ui_Setting);
    lv_imgbtn_set_src(ui_servoVerSubBtn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_145325322, NULL);
    lv_imgbtn_set_src(ui_servoVerSubBtn, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_145325322, NULL);

    lv_obj_set_height(ui_servoVerSubBtn, 24);
    lv_obj_set_width(ui_servoVerSubBtn, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_servoVerSubBtn, 400);
    lv_obj_set_y(ui_servoVerSubBtn, 48);

    lv_obj_add_event_cb(ui_servoVerSubBtn, ui_event_servoVerSubBtn, LV_EVENT_ALL, NULL);

    // ui_servoVerOffsetLabel

    ui_servoVerOffsetLabel = lv_label_create(ui_Setting);

    lv_obj_set_width(ui_servoVerOffsetLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_servoVerOffsetLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_servoVerOffsetLabel, 152);
    lv_obj_set_y(ui_servoVerOffsetLabel, 56);

    lv_label_set_text(ui_servoVerOffsetLabel, "0 °");

    lv_obj_set_style_text_font(ui_servoVerOffsetLabel, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_servoHorSubBtn

    ui_servoHorSubBtn = lv_imgbtn_create(ui_Setting);
    lv_imgbtn_set_src(ui_servoHorSubBtn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_145325322, NULL);
    lv_imgbtn_set_src(ui_servoHorSubBtn, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_145325322, NULL);

    lv_obj_set_height(ui_servoHorSubBtn, 24);
    lv_obj_set_width(ui_servoHorSubBtn, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_servoHorSubBtn, 400);
    lv_obj_set_y(ui_servoHorSubBtn, 18);

    lv_obj_add_event_cb(ui_servoHorSubBtn, ui_event_servoHorSubBtn, LV_EVENT_ALL, NULL);

    // ui_servoVerAddBtn

    ui_servoVerAddBtn = lv_imgbtn_create(ui_Setting);
    lv_imgbtn_set_src(ui_servoVerAddBtn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_565378741, NULL);
    lv_imgbtn_set_src(ui_servoVerAddBtn, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_565378741, NULL);

    lv_obj_set_height(ui_servoVerAddBtn, 24);
    lv_obj_set_width(ui_servoVerAddBtn, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_servoVerAddBtn, 440);
    lv_obj_set_y(ui_servoVerAddBtn, 48);

    lv_obj_add_event_cb(ui_servoVerAddBtn, ui_event_servoVerAddBtn, LV_EVENT_ALL, NULL);

    // ui_soundSpeedLabel

    ui_soundSpeedLabel = lv_label_create(ui_Setting);

    lv_obj_set_width(ui_soundSpeedLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_soundSpeedLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_soundSpeedLabel, 152);
    lv_obj_set_y(ui_soundSpeedLabel, 104);

    lv_label_set_text(ui_soundSpeedLabel, "340 m/s");

    lv_obj_set_style_text_font(ui_soundSpeedLabel, &ui_font_Font1, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Home_screen_init();
    ui_MeasureScreen_screen_init();
    ui_Setting_screen_init();
    lv_disp_load_scr(ui_Home);
}

