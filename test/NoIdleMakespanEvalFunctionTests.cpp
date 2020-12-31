#include <catch2/catch.hpp>
#include <vector>

#include "../src/Schedule.hpp"
#include "../src/Instance.hpp"
#include "../src/NoIdleMakespanEvalFunction.hpp"

using namespace fsp;


TEST_CASE("No-idle makespan full evaluation example gives the correct value", "[fsp]")
{
  std::vector<unsigned> pts = {1, 2, 1, 1, //
                               1, 1, 2, 2, //
                               3, 1, 1, 1};
  Instance dt(pts, 3);
  NoIdleMakespanEvalFunction eval(dt);
  Schedule schedule({ 0, 1, 2 });
  REQUIRE(eval(schedule) == 10.0);
}