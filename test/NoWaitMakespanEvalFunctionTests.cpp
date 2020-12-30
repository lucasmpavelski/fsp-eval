#include <catch2/catch.hpp>
#include <vector>

#include "../src/Schedule.hpp"
#include "../src/FSPData.hpp"
#include "../src/NoWaitMakespanEvalFunction.hpp"


TEST_CASE("No-Wait makespan full evaluation example gives the correct value", "[fsp]")
{
  std::vector<unsigned> pts = {1, 2, 1, 1, //
                               1, 1, 2, 2, //
                               3, 1, 1, 1};
  FSPData dt(pts, 3);
  NoWaitMakespanEvalFunction eval(dt);
  Schedule schedule({ 0, 1, 2 });
  REQUIRE(eval(schedule) == 9.0);
}