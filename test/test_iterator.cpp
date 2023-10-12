#include "catch.hpp"

#include <iterator>

#include "ckstl/iterator.h"


TEST_CASE("PointerIterator satisfies concepts", "[Iterator]") {
    STATIC_REQUIRE(std::input_iterator<ck::PointerIterator<int>>);
    STATIC_REQUIRE(std::forward_iterator<ck::PointerIterator<int>>);
    STATIC_REQUIRE(std::bidirectional_iterator<ck::PointerIterator<int>>);
    STATIC_REQUIRE(std::random_access_iterator<ck::PointerIterator<int>>);
    STATIC_REQUIRE(std::contiguous_iterator<ck::PointerIterator<int>>);
}
