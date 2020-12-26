#include "../catch.hpp"

#include "container/vector.h"


using namespace ck;

TEST_CASE("Vector default construction") {
Vector<int> vector;

REQUIRE(vector.size() == 0);
REQUIRE(vector.capacity() == 0);
REQUIRE_THROWS(vector.get(0));
}

TEST_CASE("Vector construction with custom initialization") {
Vector<int> vector{2};

REQUIRE(vector.size() == 2);
REQUIRE(vector.capacity() == 2);
REQUIRE(vector[0] == 0);
REQUIRE(vector[1] == 0);
REQUIRE_THROWS(vector.get(2));
}

TEST_CASE("Vector construction with multiple copies") {
Vector<int> vector{2, 1};

REQUIRE(vector.size() == 2);
REQUIRE(vector.capacity() == 2);
REQUIRE(vector[0] == 1);
REQUIRE(vector[1] == 1);
REQUIRE_THROWS(vector.get(3));
}

TEST_CASE("Vector element addition") {
Vector<int> vector;
vector.push_back(1);

REQUIRE(vector.size() == 1);
}

TEST_CASE("Vector resize smaller") {
Vector<int> vector{3};
vector.resize(1);

REQUIRE(vector.size() == 1);
REQUIRE(vector.capacity() == 3);
}

TEST_CASE("Vector resize larger") {
Vector<int> vector{3};
vector.resize(5);

REQUIRE(vector.size() == 5);
REQUIRE(vector.capacity() == 6);
}

TEST_CASE("Vector resize larger more than geometric growth") {
Vector<int> vector{3};
vector.resize(7);

REQUIRE(vector.size() == 7);
REQUIRE(vector.capacity() == 7);
}
