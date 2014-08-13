cmake_minimum_required(VERSION 2.8)

INCLUDE(CMakeForceCompiler)
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(arm-none-eabi-g++ GNU)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)

set(CMAKE_COMPILE_FLAGS "-I${CMAKE_SOURCE_DIR} -Wno-main -std=gnu11")
set(CMAKE_LINK_FLAGS "-L ${CMAKE_SOURCE_DIR}/ld -nostartfiles")

add_executable(main.elf init_vector.c init.c lm3s/adc.c lm3s/clock.c main.c)
set_target_properties(main.elf PROPERTIES
	LINK_FLAGS "${CMAKE_LINK_FLAGS} -T lm3s.ld"
	COMPILE_FLAGS "${CMAKE_COMPILE_FLAGS} -DLM3S3748=11 -include config/lm3s.h")


