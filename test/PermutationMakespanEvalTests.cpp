#include <catch2/catch.hpp>
#include <vector>

#include "../src/Schedule.hpp"
#include "../src/FSPData.hpp"
#include "../src/PermutationMakespanEvalFunction.hpp"


TEST_CASE("Waits for previous operation to complete", "[fsp]")
{
  const auto wait_time = 10;
  std::vector<unsigned> pts = { wait_time, 1 };
  FSPData fspData(pts, 1);
  PermutationMakespanEvalFunction eval(fspData);
  Schedule schedule({ 0 });

  const auto makespan = wait_time + 1.0;
  REQUIRE(eval(schedule) == makespan);
}

TEST_CASE("Waits for next machine to be available", "[fsp]")
{
  const auto wait_time = 10;
  std::vector<unsigned> pts = { 1, wait_time, 1, 1 };
  FSPData fspData(pts, 2);
  PermutationMakespanEvalFunction eval(fspData);
  Schedule schedule({ 0, 1 });

  const auto makespan = wait_time + 2.0;
  REQUIRE(eval(schedule) == makespan);
}