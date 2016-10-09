cmake_minimum_required(VERSION 3.0)
set(CMAKE_USE_RELATIVE_PATHS TRUE)

find_package(PkgConfig)

set(WARN_FLAGS "${WARN_FLAGS} -Wall -Wextra -Wundef")
set(WARN_FLAGS_C "${WARN_FLAGS_C} -Wold-style-definition -Wmissing-prototypes -Wstrict-prototypes")

option(WERROR "All warnings are errors" on)
if (WERROR)
	set(WARN_FLAGS "${WARN_FLAGS} -Werror")
endif()

option(SANITIZE_UNDEF "Enable undefined sanitizer" on)
option(SANITIZE_ADDR "Enable address sanitizer" on)
if (SANITIZE_UNDEF)
	set(EXTRA_FLAGS "${EXTRA_FLAGS} -fsanitize=undefined")
endif()

if (SANITIZE_ADDR)
	set(EXTRA_FLAGS "${EXTRA_FLAGS} -fsanitize=address")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_FLAGS} ${WARN_FLAGS_C} ${WARN_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS} ${WARN_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXTRA_FLAGS}")

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

pkg_search_module(HIDAPI REQUIRED IMPORTED_TARGET hidapi-libusb hidapi-hidraw)

add_executable(kinetis-loader kinetis-loader.c)
target_link_libraries(kinetis-loader PkgConfig::HIDAPI)

