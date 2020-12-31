#pragma once

#include "Instance.hpp"
#include "Neighbor.hpp"
#include "NoIdleNeighborEvalCompiler.hpp"
#include "Schedule.hpp"

namespace fsp {

class NoIdleFlowtimeNeighborEvalFunction
{
  NoIdleNeighborEvalCompiler compiler;

public:
  explicit NoIdleFlowtimeNeighborEvalFunction(const Instance &data) : compiler{ data } {}

  auto operator()(const Schedule &perm, const Neighbor &ngh) -> double
  {
    const auto move = ngh.firstSecond();
    compiler.compile(perm, move);
    return compiler.sumCompletionTimes();
  }
};

}// namespace fsp