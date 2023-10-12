#include "catch.hpp"

#include "ckstl/minmax.h"
#include "ckstl/vector.h"


using namespace ck;

TEST_CASE("Min", "[Minmax]") {
    REQUIRE(min(1, 2) == 1);
    REQUIRE(min(2, 1) == 1);
    REQUIRE(min(-2, 1) == -2);

    STATIC_REQUIRE(min(1, 3) == 1);
}

TEST_CASE("Max", "[Minmax]") {
    REQUIRE(max(1, 2) == 2);
    REQUIRE(max(2, 1) == 2);
    REQUIRE(max(-2, 1) == 1);

    STATIC_REQUIRE(max(1, 3) == 3);
}

TEST_CASE("Min Element", "[Minmax]") {
    Vector<int> vec;
    REQUIRE(min_element(vec.begin(), vec.end()) == vec.end());

    vec.push_back(3);
    vec.push_back(5);
    vec.push_back(2);
    vec.push_back(7);

    REQUIRE(min_element(vec.begin(), vec.end()) == vec.begin() + 2);
}


TEST_CASE("Max Element", "[Minmax]") {
    Vector<int> vec;
    REQUIRE(max_element(vec.begin(), vec.end()) == vec.end());

    vec.push_back(3);
    vec.push_back(7);
    vec.push_back(5);
    vec.push_back(2);

    REQUIRE(max_element(vec.begin(), vec.end()) == vec.begin() + 1);
}
