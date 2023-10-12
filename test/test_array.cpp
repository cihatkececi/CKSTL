#include "catch.hpp"

#include "ckstl/array.h"


using namespace ck;

TEST_CASE("Array default construction", "[Array]") {
    Array<int, 0> array;

    REQUIRE(array.size() == 0);
    REQUIRE_THROWS(array.at(0));
}
