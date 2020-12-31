#include <catch2/catch.hpp>
#include <random>
#include <vector>

#include "../src/Schedule.hpp"
#include "../src/Neighbor.hpp"
#include "../src/Instance.hpp"
#include "../src/PermutationMakespanEvalFunction.hpp"
#include "../src/PermutationMakespanNeighborEvalFunction.hpp"

using namespace fsp;


TEST_CASE("Permutation makespan neighbors give the same results as full evaluation", "[fsp]")
{
  long seed = 123L;
  std::default_random_engine rng(seed);

  const auto noJobs = 50;
  const auto noMachines = 10;
  const auto maxPt = 99;
  Instance instance(noJobs, noMachines, rng, maxPt);

  PermutationMakespanEvalFunction eval(instance);
  PermutationMakespanNeighborEvalFunction neighborEval(instance);

  Schedule schedule(instance.noJobs());

  std::uniform_int_distribution<int> dist(0, instance.noJobs() - 1);
  for (int i = 0; i < instance.noJobs(); i++) {
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
