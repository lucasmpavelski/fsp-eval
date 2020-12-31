#pragma once

#include "Neighbor.hpp"
#include "NoIdleNeighborEvalCompiler.hpp"
#include "Schedule.hpp"
#include "Instance.hpp"

namespace fsp {

class NoIdleMakespanNeighborEvalFunction
{
  NoIdleNeighborEvalCompiler compiler;

public:
  explicit NoIdleMakespanNeighborEvalFunction(const Instance &data) : compiler{ data } {}

  auto operator()(const Schedule &perm, const Neighbor &ngh) -> double
  {
    const auto move = ngh.firstSecond();
    compiler.compile(perm, move);
    return compiler.compiledCompletionTime(static_cast<int>(perm.size()) - 1);
  }
};

}// namespace fsp