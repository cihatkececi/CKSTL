cmake_minimum_required(VERSION 3.12)



add_executable(tests
        catch.hpp
        main.cpp
        container/vector.cpp
        container/array.cpp
        container/list.cpp
        )

target_link_libraries(tests PRIVATE ckstl)
target_compile_options(tests PRIVATE --coverage -O0)
target_link_options(tests PRIVATE -lgcov --coverage)

include(CTest)
#include(Catch)
#catch_discover_tests(tests)

include(ParseAndAddCatchTests)
ParseAndAddCatchTests(tests)

