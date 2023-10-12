#include "catch.hpp"

#include "ckstl/heap.h"
#include "ckstl/vector.h"

using namespace ck;

TEST_CASE("Make Heap", "[Heap]") {
    SECTION("Max Heap") {
        Vector<int> v{3, 2, 4, 1, 5, 9};

        make_heap(v.begin(), v.end());
        REQUIRE(v[0] == 9);
        REQUIRE(v[0] >= v[1]);
        REQUIRE(v[0] >= v[2]);
        REQUIRE(v[1] >= v[3]);
        REQUIRE(v[1] >= v[4]);
        REQUIRE(v[2] >= v[5]);
    }

    SECTION("Min Heap") {
        Vector<int> v{3, 2, 4, 1, 5, 9};
        make_heap(v.begin(), v.end(), Greater<int>{});
        REQUIRE(v[0] == 1);
        REQUIRE(v[0] <= v[1]);
        REQUIRE(v[0] <= v[2]);
        REQUIRE(v[1] <= v[3]);
        REQUIRE(v[1] <= v[4]);
        REQUIRE(v[2] <= v[5]);
    }
}

TEST_CASE("Push Heap", "[Heap]") {
    Vector<int> v{3, 2, 4, 1, 5, 9};

    make_heap(v.begin(), v.end());

    v.push_back(10);
    push_heap(v.begin(), v.end());
    REQUIRE(v[0] == 10);
    REQUIRE(v[0] >= v[1]);
    REQUIRE(v[0] >= v[2]);
    REQUIRE(v[1] >= v[3]);
    REQUIRE(v[1] >= v[4]);
    REQUIRE(v[2] >= v[5]);
    REQUIRE(v[2] >= v[6]);

    v.push_back(5);
    push_heap(v.begin(), v.end());
    REQUIRE(v[0] == 10);
    REQUIRE(v[0] >= v[1]);
    REQUIRE(v[0] >= v[2]);
    REQUIRE(v[1] >= v[3]);
    REQUIRE(v[1] >= v[4]);
    REQUIRE(v[2] >= v[5]);
    REQUIRE(v[2] >= v[6]);
    REQUIRE(v[3] >= v[7]);
}

TEST_CASE("Pop Heap", "[Heap]") {
    Vector<int> v{3, 2, 4, 1, 5, 9};

    make_heap(v.begin(), v.end());

    pop_heap(v.begin(), v.end());
    REQUIRE(v.rat(0) == 9);
    REQUIRE(v[0] > v[1]);
    REQUIRE(v[0] > v[2]);
    REQUIRE(v[1] > v[3]);
    REQUIRE(v[1] > v[4]);

    v.pop_back();

    pop_heap(v.begin(), v.end());
    REQUIRE(v.rat(0) == 5);
    REQUIRE(v[0] > v[1]);
    REQUIRE(v[0] > v[2]);
    REQUIRE(v[1] > v[3]);
}
