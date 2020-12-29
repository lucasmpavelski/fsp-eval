#include <catch2/catch.hpp>
#include <vector>

#include "../src/Schedule.hpp"

TEST_CASE("Create default ordered schedule", "[fsp]")
{
  Schedule schedule(3);

  REQUIRE(schedule[0] == 0);
  REQUIRE(schedule[1] == 1);
  REQUIRE(schedule[2] == 2);
}

TEST_CASE("Throws on invalid permutation", "[fsp]")
{
  REQUIRE_THROWS(Schedule({ 1, 2, 3 }));
}