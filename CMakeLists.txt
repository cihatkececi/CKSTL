cmake_minimum_required(VERSION 3.12)
project(CKSTL CXX)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()


set(SRC_FILES
        )

set(HEADER_FILES
        include/container/vector.h
        include/container/array.h
        include/container/list.h
        include/container/memutil.h)

include_directories(include)

#add_library(ckstl ${SRC_FILES} ${HEADER_FILES})
add_library(ckstl INTERFACE)
#target_include_directories(ckstl INTERFACE include)

# Testing
option(ENABLE_TESTING "Enable Testing" TRUE)

if (ENABLE_TESTING)
    enable_testing()
    add_subdirectory(test)
endif ()


