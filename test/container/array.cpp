#include "../catch.hpp"

#include "container/array.h"


using namespace ck;

TEST_CASE("Array default construction") {
    Array<int, 0> array;

    REQUIRE(array.size() == 0);
    REQUIRE_THROWS(array.get(0));
}
