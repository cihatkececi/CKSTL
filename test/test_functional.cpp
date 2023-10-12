#include "catch.hpp"

#include "ckstl/functional.h"


using namespace ck;

TEST_CASE("Functional Less", "[Functional]") {
    REQUIRE(Less<int>{}(1, 2) == true);
    REQUIRE(Less<int>{}(2, 1) == false);
    REQUIRE(Less<float>{}(1.0, 2.0) == true);
    REQUIRE(Less<float>{}(2.0, 1.0) == false);
}

TEST_CASE("Functional Greater", "[Functional]") {
    REQUIRE(Greater<int>{}(1, 2) == false);
    REQUIRE(Greater<int>{}(2, 1) == true);
    REQUIRE(Greater<float>{}(1.0, 2.0) == false);
    REQUIRE(Greater<float>{}(2.0, 1.0) == true);
}
