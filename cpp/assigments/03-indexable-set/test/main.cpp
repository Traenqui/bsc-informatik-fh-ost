#include "indexableSet.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("IndexableSet basic functionality", "[indexableSet]")
{
  IndexableSet<int> s;

  SECTION("Empty set")
  {
    REQUIRE(s.empty());
    REQUIRE_THROWS_AS(s.front(), std::out_of_range);
    REQUIRE_THROWS_AS(s.back(), std::out_of_range);
    REQUIRE_THROWS_AS(s[0], std::out_of_range);
    REQUIRE_THROWS_AS(s.at(0), std::out_of_range);
  }

  SECTION("Insert elements")
  {
    s.insert(3);
    s.insert(1);
    s.insert(2);
    REQUIRE(s.size() == 3);
    REQUIRE(s.front() == 1);
    REQUIRE(s.back() == 3);
  }

  SECTION("Indexing positive")
  {
    s = {1, 2, 3};
    REQUIRE(s[0] == 1);
    REQUIRE(s[1] == 2);
    REQUIRE(s[2] == 3);
    REQUIRE(s.at(0) == 1);
    REQUIRE(s.at(1) == 2);
    REQUIRE(s.at(2) == 3);
  }

  SECTION("Indexing negative")
  {
    s = {1, 2, 3};
    REQUIRE(s[-1] == 3);
    REQUIRE(s[-2] == 2);
    REQUIRE(s[-3] == 1);
    REQUIRE(s.at(-1) == 3);
    REQUIRE(s.at(-2) == 2);
    REQUIRE(s.at(-3) == 1);
  }

  SECTION("Out of range")
  {
    s = {1, 2, 3};
    REQUIRE_THROWS_AS(s[3], std::out_of_range);
    REQUIRE_THROWS_AS(s[-4], std::out_of_range);
    REQUIRE_THROWS_AS(s.at(3), std::out_of_range);
    REQUIRE_THROWS_AS(s.at(-4), std::out_of_range);
  }

  SECTION("Constructors")
  {
    IndexableSet<int> s1;
    REQUIRE(s1.empty());

    IndexableSet<int> s2 = {1, 2, 3};
    REQUIRE(s2.size() == 3);
    REQUIRE(s2[0] == 1);

    std::set<int> base = {4, 5, 6};
    IndexableSet<int> s3(base.begin(), base.end());
    REQUIRE(s3.size() == 3);
    REQUIRE(s3[0] == 4);
  }
}

TEST_CASE("IndexableSet with custom comparator", "[indexableSet]")
{
  IndexableSet<std::string, caselessCompare> s;

  s.insert("Apple");
  s.insert("banana");
  s.insert("Cherry");

  REQUIRE(s.size() == 3);
  REQUIRE(s[0] == "Apple");
  REQUIRE(s[1] == "banana");
  REQUIRE(s[2] == "Cherry");
}
