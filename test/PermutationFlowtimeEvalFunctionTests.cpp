#include <catch2/catch.hpp>
#include <vector>

#include "../src/Schedule.hpp"
#include "../src/Instance.hpp"
#include "../src/PermutationFlowtimeEvalFunction.hpp"

using namespace fsp;

TEST_CASE("Sums all completion times", "[fsp]")
{
  const auto wait_time = 10;
  std::vector<unsigned> pts = { 1, wait_time, 1, 1 };
  Instance instance(pts, 2);
  PermutationFlowtimeEvalFunction eval(instance);
  Schedule schedule({ 0, 1 });

  const auto ct_0 = wait_time + 1.0;
  const auto ct_1 = wait_time + 2.0;
  REQUIRE(eval(schedule) == ct_0 + ct_1);
}