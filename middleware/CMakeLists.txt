file(GLOB_RECURSE SOURCES lvgl/src/*.c)
foreach(FILE IN ITEMS ${SOURCES})
    sdk_src(${FILE})
endforeach()

sdk_inc(${CMAKE_CURRENT_SOURCE_DIR})
sdk_inc(${CMAKE_CURRENT_SOURCE_DIR}/lvgl)
