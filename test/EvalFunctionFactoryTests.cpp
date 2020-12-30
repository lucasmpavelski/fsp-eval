#include <catch2/catch.hpp>
#include <vector>

#include <memory>
#include <vector>

#include "../src/FSPData.hpp"
#include "../src/EvalFunction.hpp"
#include "../src/EvalFunctionFactory.hpp"

TEST_CASE("Factory builds the eval function with right type and objective", "[fsp]") {
  const std::vector<unsigned> procTimes = { 1, 2, 3, 4, 5, 6 };
  const int no_jobs = 2;
  FSPData fspData(procTimes, no_jobs);
  std::unique_ptr<EvalFunction> eval = EvalFunctionFactory::build(Type::PERMUTATION, Objective::MAKESPAN, fspData);
  PermutationMakespanEvalFunction eval2(fspData);
  REQUIRE(*eval == eval2);
}