cmake_minimum_required(VERSION 3.20)

file(GLOB_RECURSE CKSTL_TEST_FILES *.cpp)

add_executable(ckstl_tests ${CKSTL_TEST_FILES} catch.hpp)

target_link_libraries(ckstl_tests PRIVATE ckstl)
target_include_directories(ckstl_tests PRIVATE ${CKSTL_INCLUDE_DIR})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES ".*Clang")
    option(ENABLE_COVERAGE "Enable Coverage Reporting" FALSE)

    if (ENABLE_COVERAGE)
        target_compile_options(ckstl_tests PRIVATE --coverage -g)
        target_link_libraries(ckstl_tests PRIVATE -lgcov --coverage)
    endif ()
endif ()


include(CTest)
include(Catch)
catch_discover_tests(ckstl_tests)

