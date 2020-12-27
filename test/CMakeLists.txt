cmake_minimum_required(VERSION 3.12)



add_executable(tests
        catch.hpp
        main.cpp
        container/vector.cpp
        container/array.cpp
        container/list.cpp
        )

target_link_libraries(tests PRIVATE ckstl)

include(CTest)
#include(Catch)
#catch_discover_tests(tests)

include(ParseAndAddCatchTests)
ParseAndAddCatchTests(tests)

