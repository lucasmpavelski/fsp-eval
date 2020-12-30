#include <catch2/catch.hpp>
#include <vector>

#include "../src/Schedule.hpp"
#include "../src/FSPData.hpp"
#include "../src/NoWaitFlowtimeEvalFunction.hpp"


TEST_CASE("No-wait flowtime full evaluation example gives the correct value", "[fsp]")
{
  std::vector<unsigned> pts = {1, 2, 1, 1, //
                               1, 1, 2, 2, //
                               3, 1, 1, 1};
  FSPData dt(pts, 3);
  NoWaitFlowtimeEvalFunction eval(dt);
  Schedule schedule({ 0, 1, 2 });
  REQUIRE(eval(schedule) == 5 + 8 + 9);
}