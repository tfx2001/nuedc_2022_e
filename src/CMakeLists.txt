sdk_app_src(main.c)
# sdk_app_src(tmp275.c)
sdk_app_src(lv_port.c)
sdk_app_src(ns2009.c)
sdk_app_src(audio_capture.c)
sdk_app_src(servo.c)
sdk_app_src(setting.c)

sdk_app_inc(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(lvgl_ui)
