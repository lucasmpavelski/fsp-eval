#include <catch2/catch.hpp>
#include <vector>

#include "../src/Schedule.hpp"
#include "../src/Instance.hpp"
#include "../src/PermutationMakespanEvalFunction.hpp"

using namespace fsp;


TEST_CASE("Waits for previous operation to complete", "[fsp]")
{
  const auto wait_time = 10;
  std::vector<unsigned> pts = { wait_time, 1 };
  Instance instance(pts, 1);
  PermutationMakespanEvalFunction eval(instance);
  Schedule schedule({ 0 });

  const auto makespan = wait_time + 1.0;
  REQUIRE(eval(schedule) == makespan);
}

TEST_CASE("Waits for next machine to be available", "[fsp]")
{
  const auto wait_time = 10;
  std::vector<unsigned> pts = { 1, wait_time, 1, 1 };
  Instance instance(pts, 2);
  PermutationMakespanEvalFunction eval(instance);
  Schedule schedule({ 0, 1 });

  const auto makespan = wait_time + 2.0;
  REQUIRE(eval(schedule) == makespan);
}