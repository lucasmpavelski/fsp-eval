#include <catch2/catch.hpp>
#include <vector>

#include <vector>

#include "../src/Instance.hpp"

using namespace fsp;

TEST_CASE("FSP data load from vector", "[fsp]")
{
  const std::vector<unsigned> procTimes = { 1, 2, 3, 4, 5, 6 };
  const int no_jobs = 2;
  Instance instance(procTimes, no_jobs);

  SECTION("number of machines is determined")
  {
    REQUIRE(instance.noMachines() == 3);
  }

  SECTION("vector is read by row")
  {
    REQUIRE(instance.pt(0, 1) == 2);
  }
}


TEST_CASE("FSP data load from vector by jobs", "[fsp]")
{
  const std::vector<unsigned> procTimes = { 1, 2, 3, 4, 5, 6 };
  const int no_jobs = 2;
  const bool jobsByMachines = true;
  Instance instance(procTimes, no_jobs, jobsByMachines);

  SECTION("vector is read by row")
  {
    REQUIRE(instance.pt(0, 1) == 4);
  }
}


TEST_CASE("FSP data load from file", "[fsp]")
{
  Instance instance("test/instance.txt");

  SECTION("dimensions are correct")
  {
    REQUIRE(instance.noJobs() == 4);
    REQUIRE(instance.noMachines() == 5);
  }

  SECTION("processing times are loaded")
  {
    REQUIRE(instance.pt(0, 0) == 5);
    REQUIRE(instance.pt(0, 1) == 9);
  }
}

TEST_CASE("FSP data can be compared with equals operator", "[fsp]")
{
  Instance instance1("test/instance.txt");
  Instance instance2("test/instance.txt");

  REQUIRE(instance1 == instance2);
}
