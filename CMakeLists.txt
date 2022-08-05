cmake_minimum_required(VERSION 3.13)

set(CONFIG_FREERTOS 1)

set(SES_TOOLCHAIN_VARIANT "Andes")
set(CONFIG_HPM_MATH 1)
set(HPM_MATH_SES_LIB "libdspf")

find_package(hpm-sdk REQUIRED HINTS $ENV{HPM_SDK_BASE})

project(2022_nuedc)
sdk_ses_compile_options(-mabi=ilp32f)
sdk_ses_compile_options(-march=rv32imafc)

add_subdirectory(middleware)

sdk_compile_definitions(-D__freertos_irq_stack_top=_stack)
sdk_compile_definitions(-DCONFIG_FREERTOS=1)
sdk_compile_definitions(-DUSE_NONVECTOR_MODE=1)
sdk_compile_definitions(-DDISABLE_IRQ_PREEMPTIVE=1)

# Application
add_subdirectory(src)

generate_ses_project()
