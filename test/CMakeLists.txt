cmake_minimum_required(VERSION 3.12)



add_executable(tests
        catch.hpp
        main.cpp
        container/vector.cpp
        container/array.cpp
        container/list.cpp
        )

target_link_libraries(tests PRIVATE ckstl)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES ".*Clang")
    option(ENABLE_COVERAGE "Enable Coverage Reporting" FALSE)

    if (ENABLE_COVERAGE)
        target_compile_options(tests PRIVATE --coverage -O0)
        target_link_libraries(tests PRIVATE -lgcov --coverage)
#        add_definitions(--coverage -O0)
#        set(LINKER_FLAGS "${LINKER_FLAGS} -lgcov --coverage")
    endif ()
endif ()


include(CTest)
#include(Catch)
#catch_discover_tests(tests)

include(ParseAndAddCatchTests)
ParseAndAddCatchTests(tests)

