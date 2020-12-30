#pragma once

#include "FSPData.hpp"
#include "Neighbor.hpp"
#include "NoIdleNeighborEvalCompiler.hpp"
#include "Schedule.hpp"

class NoIdleFlowtimeNeighborEvalFunction
{
  NoIdleNeighborEvalCompiler compiler;

public:
  explicit NoIdleFlowtimeNeighborEvalFunction(const FSPData &data) : compiler{ data } {}

  auto operator()(const Schedule &perm, const Neighbor &ngh) -> double
  {
    const auto move = ngh.firstSecond();
    compiler.compile(perm, move);
    return compiler.sumCompletionTimes();
  }
};