#include <catch2/catch.hpp>
#include <vector>

#include <memory>
#include <vector>

#include "../src/Instance.hpp"
#include "../src/EvalFunction.hpp"
#include "../src/EvalFunctionFactory.hpp"

using namespace fsp;

TEST_CASE("Factory builds the eval function with right type and objective", "[fsp]") {
  const std::vector<unsigned> procTimes = { 1, 2, 3, 4, 5, 6 };
  const int no_jobs = 2;
  Instance instance(procTimes, no_jobs);
  std::unique_ptr<EvalFunction> eval = EvalFunctionFactory::build(Type::PERMUTATION, Objective::MAKESPAN, instance);
  PermutationMakespanEvalFunction eval2(instance);
  REQUIRE(*eval == eval2);
}