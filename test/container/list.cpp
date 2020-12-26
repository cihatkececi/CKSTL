#include "../catch.hpp"

#include "container/list.h"


using namespace ck;

TEST_CASE("List default construction") {
    List<int> list;

    REQUIRE(list.size() == 0);
    REQUIRE_THROWS(list.front());
    REQUIRE_THROWS(list.back());
    REQUIRE(list.begin() == list.end());
}

TEST_CASE("List push back") {
    List<int> list;
    list.push_back(1);
    REQUIRE(list.size() == 1);
    REQUIRE(list.front() == 1);
    REQUIRE(list.back() == 1);

    list.push_back(2);

    REQUIRE(list.size() == 2);
    REQUIRE(list.front() == 1);
    REQUIRE(list.back() == 2);
}

TEST_CASE("List push front") {
    List<int> list;
    list.push_front(2);
    REQUIRE(list.size() == 1);

    list.push_front(1);

    REQUIRE(list.size() == 2);
    REQUIRE(list.front() == 1);
    REQUIRE(list.back() == 2);
}

TEST_CASE("List copy construction") {
    List<int> list;
    list.push_back(1);

    List<int> list2{list};

    REQUIRE(list2.size() == list.size());
    REQUIRE(list2.front() == 1);
    REQUIRE(list2.back() == 1);
}

TEST_CASE("List move construction") {
    List<int> list;
    list.push_back(1);

    List<int> list2{std::move(list)};

    REQUIRE(list2.size() == 1);
    REQUIRE(list2.front() == 1);
    REQUIRE(list2.back() == 1);

    REQUIRE(list.size() == 0);
}
