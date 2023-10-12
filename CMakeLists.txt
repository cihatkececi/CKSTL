cmake_minimum_required(VERSION 3.20)
project(CKSTL CXX)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	option(USE_ASAN "Use the address sanitizer" OFF)

	if (MSVC)
		add_compile_options(/W4)

		if (USE_ASAN)
			add_compile_options(/fsanitize=address)
			add_link_options(/fsanitize=address)
		endif ()
	else ()
		add_compile_options(-Wall -Wpedantic -Wextra)

		if (USE_ASAN)
			add_compile_options(-fsanitize=address)
			add_link_options(-fsanitize=address)
		endif ()
	endif ()
endif ()

file(GLOB_RECURSE CKSTL_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}include/*.h)

set(CKSTL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(ckstl INTERFACE ${CKSTL_HEADER_FILES})
target_include_directories(ckstl INTERFACE ${CKSTL_INCLUDE_DIR})

# Testing
include(CTest)

if (BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif (BUILD_TESTING)


