#include <catch2/catch.hpp>
#include <random>
#include <vector>

#include "../src/Schedule.hpp"
#include "../src/Neighbor.hpp"
#include "../src/FSPData.hpp"
#include "../src/NoIdleMakespanEvalFunction.hpp"
#include "../src/NoIdleMakespanNeighborEvalFunction.hpp"


TEST_CASE("No-idle makespan neighbors give the same results as full evaluation", "[fsp]")
{
  long seed = 123L;
  std::default_random_engine rng(seed);

  const auto noJobs = 50;
  const auto noMachines = 10;
  const auto maxPt = 99;
  FSPData fspData(noJobs, noMachines, rng, maxPt);

  NoIdleMakespanEvalFunction eval(fspData);
  NoIdleMakespanNeighborEvalFunction neighborEval(fspData);

  Schedule schedule(fspData.noJobs());

  std::uniform_int_distribution<int> dist(0, fspData.noJobs() - 1);
  for (int i = 0; i < fspData.noJobs(); i++) {
    int from = 0;
    int to = 0;
    do {
      from = dist(rng);
      to = dist(rng);
    } while (from - 1 == to || from == to);
    Neighbor neighbor(from, to);
    Schedule moved = neighbor.move(schedule);
    REQUIRE(eval(moved) == neighborEval(schedule, neighbor));
  }
}
