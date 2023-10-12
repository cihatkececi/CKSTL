#include "catch.hpp"

#include "ckstl/unique_ptr.h"

using namespace ck;

TEST_CASE("Unique pointer array element", "[UniquePtr]") {
    UniquePtr<int[]> arr(new int[10]);

    REQUIRE_NOTHROW(arr[5] = 5);
    REQUIRE(arr[5] == 5);
}
