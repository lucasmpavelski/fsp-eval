#pragma once

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "FSPData.hpp"
#include "Neighbor.hpp"
#include "NoWaitEvalFunction.hpp"
#include "Schedule.hpp"

/**
 * Fast evaluation for No-wait flowshop as show in
 * An improved iterated greedy algorithm for the no-waitflow shop scheduling
 * problem with makespan criterion
 * by Quan-Ke Pan, Ling Wang and Bao-Hua Zhao
 */
class NoWaitMakespanNeighborEvalFunction {
  const FSPDataStatistics stats;
  [[maybe_unused]] NoWaitEvalFunction& fullEval;

  static int asInt(unsigned pt) {
    return static_cast<int>(pt);
  }

  auto partialMakespan(const Schedule& sol, int cmaxSol, unsigned j) -> int {
    int pj = asInt(sol[j]);
    const auto& T = stats.jobProcTimesRef();

    if (j == 0) {
      int p1 = asInt(sol[1]);
      return cmaxSol - fullEval.delay(pj, p1);
    }

    int pj_m1 = asInt(sol[j - 1]);
    if (j == sol.size() - 1) {
      return cmaxSol - fullEval.delay(pj_m1, pj) - asInt(T[pj]) + asInt(T[pj_m1]);
    }

    int pj_p1 = asInt(sol[j + 1]);
    return cmaxSol - fullEval.delay(pj_m1, pj) - fullEval.delay(pj, pj_p1) +
           fullEval.delay(pj_m1, pj_p1);
  }

  auto neighborMakespan(int partialCmax, const Schedule& sol, int j, int k)
      -> int {
    int pj = asInt(sol[j]);
    const auto& T = stats.jobProcTimesRef();

    if (k == 0) {
      return partialCmax + fullEval.delay(pj, asInt(sol[0]));
    }

    int pk_m1 = j < k ? asInt(sol[k]) : asInt(sol[k - 1]);
    if (k == sol.size() - 1) {
      return partialCmax + fullEval.delay(pk_m1, pj) - asInt(T[pk_m1]) + asInt(T[pj]);
    }

    int pk = j < k ? asInt(sol[k + 1]) : asInt(sol[k]);
    return partialCmax + fullEval.delay(pk_m1, pj) + fullEval.delay(pj, pk) -
           fullEval.delay(pk_m1, pk);
  }

 public:
  explicit NoWaitMakespanNeighborEvalFunction(NoWaitEvalFunction& fullEval)
      : stats(fullEval.getData()), fullEval(fullEval) {}

  auto operator()(const Schedule& sol, double solEval, const Neighbor& ngh)-> double {
    auto firstSecond = ngh.firstSecond();
    auto j = firstSecond.first;
    auto k = firstSecond.second;
    int cMax_ll = partialMakespan(sol, static_cast<int>(solEval), j);
    return neighborMakespan(cMax_ll, sol, j, k);
  }
};
