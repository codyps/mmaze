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
set(CMAKE_LINK_FLAGS "-L ${CMAKE_OUTPUT_DIR} -T ld/armv7m.lds -nostartfiles")

macro(cpp_lds _lds)
	add_custom_command(OUTPUT ${CMAKE_OUTPUT_DIR}/${_lds}
			   DEPENDS ${CMAKE_SOURCE_DIR}/${_lds}.S
			   COMMAND ${CMAKE_C_COMPILER} -E -C -P ${COMPILE_FLAGS} -
		   )
endmacro()

add_executable(lm3s.elf init_vector.c init.c lm3s/adc.c lm3s/clock.c main.c)
set_target_properties(lm3s.elf PROPERTIES
	COMPILE_FLAGS "${CMAKE_COMPILE_FLAGS} -mcpu=cortex-m3 -DLM3S3748=1 -include config/lm3s.h")

add_executable(main.elf init_vector.c init.c main_teensy.c)
set_target_properties(main.elf PROPERTIES
	COMPILE_FLAGS "${CMAKE_COMPILE_FLAGS} -mcpu=cortex-m4 -include config/k20dx128vlh5.h")

