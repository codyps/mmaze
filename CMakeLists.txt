cmake_minimum_required(VERSION 2.8)
set(CMAKE_USE_RELATIVE_PATHS TRUE)

INCLUDE(CMakeForceCompiler)
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(arm-none-eabi-g++ GNU)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)

set(CMAKE_COMPILE_FLAGS -I${CMAKE_SOURCE_DIR} -Wno-main -std=gnu11)
set(CMAKE_EXE_LINKER_FLAGS "-nostartfiles")

function(cpp_lds _target _lds_src)
	set(_lds_dummy_c ${CMAKE_BINARY_DIR}/${_target}.cpp_lds.c)
	# TODO: be more flexible here
	set(_lds_src_from_b ${CMAKE_SOURCE_DIR}/${_lds_src})
	set(_lds_out "${CMAKE_BINARY_DIR}/${_target}.lds")

	add_custom_command(OUTPUT ${_lds_dummy_c}
		COMMAND ${CMAKE_COMMAND} -E touch ${_lds_dummy_c}
		MAIN_DEPENDENCY ${_lds_out}
	)

	# Ideally this would work, but it doesn't.
	#set(_compile_flags "$<JOIN:$<TARGET_PROPERTY:${_target},COMPILE_OPTIONS>, >")
	get_target_property(_compile_flags "${_target}" COMPILE_OPTIONS)
	add_custom_command(OUTPUT ${_lds_out}
		COMMAND ${CMAKE_C_COMPILER} -E -C -P ${_lds_src_from_b} ${_compile_flags} -o ${_lds_out}
		MAIN_DEPENDENCY ${_lds_src_from_b}
		VERBATIM
	)
	target_sources(${_target} PRIVATE ${_lds_dummy_c})
	set_target_properties(${_target} PROPERTIES LINK_FLAGS "-T ${_lds_out}")
endfunction()

add_executable(lm3s.elf init_vector.c init.c lm3s/adc.c lm3s/clock.c main.c)
target_compile_options(lm3s.elf PRIVATE ${CMAKE_COMPILE_FLAGS} -mcpu=cortex-m3
	-mthumb -DLM3S3748=1 -include config/lm3s.h)
cpp_lds(lm3s.elf ld/armv7m.lds.S)

add_executable(teensy.elf init_vector.c init.c main_teensy.c)
target_compile_options(teensy.elf PRIVATE ${CMAKE_COMPILE_FLAGS} -mcpu=cortex-m4 -mthumb -include config/k20dx128vlh5.h)
cpp_lds(teensy.elf ld/armv7m.lds.S)
