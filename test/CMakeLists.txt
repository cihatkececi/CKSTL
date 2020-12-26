cmake_minimum_required(VERSION 3.12)


enable_testing()

add_executable(tests
        catch.hpp
        main.cpp
        container/vector.cpp
        container/array.cpp
        container/list.cpp
        )

target_link_libraries(tests PRIVATE ckstl)

include(CTest)
include(Catch)
catch_discover_tests(tests)

