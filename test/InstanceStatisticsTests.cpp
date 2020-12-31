#include <catch2/catch.hpp>
#include <vector>

#include "../src/InstanceStatistics.hpp"

using namespace fsp;

TEST_CASE("FSP data statistics", "[fsp]") {
  const std::vector<unsigned> procTimes = { 1, 2, 3, 4, 5, 6 };
  const int no_jobs = 2;
  Instance instance(procTimes, no_jobs);
  InstanceStatistics stats(instance);

  SECTION("sum of processing times by job is correct")
  {
    REQUIRE(stats.jobProcTime(0) == 1 + 2 + 3);
  }

  SECTION("sum of processing times by machine is correct")
  {
    REQUIRE(stats.machineProcTime(0) == 1 + 4);
  }

  SECTION("sum of total processing times is correct")
  {
    REQUIRE(stats.maxCT() == 1 + 2 + 3 + 4 + 5 + 6);
  }
}