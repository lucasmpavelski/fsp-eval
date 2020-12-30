#include <catch2/catch.hpp>
#include <vector>

#include "../src/Schedule.hpp"
#include "../src/FSPData.hpp"
#include "../src/NoIdleMakespanEvalFunction.hpp"


TEST_CASE("No-idle makespan full evaluation example gives the correct value", "[fsp]")
{
  std::vector<unsigned> pts = {1, 2, 1, 1, //
                               1, 1, 2, 2, //
                               3, 1, 1, 1};
  FSPData dt(pts, 3);
  NoIdleMakespanEvalFunction eval(dt);
  Schedule schedule({ 0, 1, 2 });
  REQUIRE(eval(schedule) == 10.0);
}