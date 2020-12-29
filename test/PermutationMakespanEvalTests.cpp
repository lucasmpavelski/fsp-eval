#include <catch2/catch.hpp>
#include <vector>

#include "../src/FSPSchedule.hpp"
#include "../src/FSPData.hpp"
#include "../src/PermutationMakespanEval.hpp"

const auto wait_time = 10;

TEST_CASE("Waits for previous operation to complete", "[fsp]")
{
  std::vector<unsigned> pts = {wait_time, 1};
  FSPData fspData(pts, 1);
  PermutationMakespanEval eval(fspData);
  FSPSchedule schedule({0});

  const auto makespan = wait_time + 1.0;
  REQUIRE(eval(schedule) == makespan);
}

TEST_CASE("Waits for next machine to be available", "[fsp]")
{
  std::vector<unsigned> pts = {1, wait_time, 1, 1};
  FSPData fspData(pts, 2);
  PermutationMakespanEval eval(fspData);
  FSPSchedule schedule({0, 1});

  const auto makespan = wait_time + 2.0;
  REQUIRE(eval(schedule) == makespan);
}