#include <catch2/catch.hpp>
#include <vector>

#include <vector>

#include "../src/FSPData.hpp"

TEST_CASE("FSP data load from vector", "[fsp]")
{
  const std::vector<unsigned> procTimes = { 1, 2, 3, 4, 5, 6 };
  const int no_jobs = 2;
  FSPData fspData(procTimes, no_jobs);

  SECTION("number of machines is determined")
  {
    REQUIRE(fspData.noMachines() == 3);
  }

  SECTION("vector is read by row")
  {
    REQUIRE(fspData.pt(0, 1) == 2);
  }
}


TEST_CASE("FSP data load from vector by jobs", "[fsp]")
{
  const std::vector<unsigned> procTimes = { 1, 2, 3, 4, 5, 6 };
  const int no_jobs = 2;
  const bool jobsByMachines = true;
  FSPData fspData(procTimes, no_jobs, jobsByMachines);

  SECTION("vector is read by row")
  {
    REQUIRE(fspData.pt(0, 1) == 4);
  }
}


TEST_CASE("FSP data load from file", "[fsp]")
{
  FSPData fspData("test/instance.txt");

  SECTION("dimensions are correct")
  {
    REQUIRE(fspData.noJobs() == 4);
    REQUIRE(fspData.noMachines() == 5);
  }

  SECTION("processing times are loaded")
  {
    REQUIRE(fspData.pt(0, 0) == 5);
    REQUIRE(fspData.pt(0, 1) == 9);
  }
}
