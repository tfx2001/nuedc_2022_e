file(GLOB_RECURSE SOURCES *.c)
foreach(FILE IN ITEMS ${SOURCES})
    sdk_src(${FILE})
endforeach()

sdk_inc(${CMAKE_CURRENT_SOURCE_DIR})

