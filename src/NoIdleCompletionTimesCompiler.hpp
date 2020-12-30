#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

#include "Schedule.hpp"
#include "FSPData.hpp"
#include "FSPDataStatistics.hpp"
#include "EvalFunction.hpp"

class NoIdleCompletionTimesCompiler
{
  const FSPData fspData;
  const FSPDataStatistics stats;

  std::vector<int> _F;
  auto F(unsigned j, unsigned m) -> int & { return _F[m * fspData.noJobs() + j]; }

public:
  explicit NoIdleCompletionTimesCompiler(const FSPData &fspData)
    : fspData(fspData), stats(fspData), _F(fspData.noJobs() * (fspData.noMachines() - 1)) {}

  void compile(const Schedule &perm,
    std::vector<unsigned> &completionTimes)
  {
    const auto noJobs = perm.size();
    const auto noMachines = fspData.noMachines();

    // forward pass calculation
    for (int k = 0; k < noMachines - 1; k++) {
      F(0, k) = fspData.pt(perm[0], k + 1);
    }
    for (int j = 1; j < noJobs; j++) {
      for (int k = 0; k < noMachines - 1; k++) {
        const int p_j_k = static_cast<int>(fspData.pt(perm[j], k));
        const int p_j_kp1 = static_cast<int>(fspData.pt(perm[j], k + 1));
        const int F_jm1_k = F(j - 1, k);
        F(j, k) = std::max(F_jm1_k - p_j_k, 0) + p_j_kp1;
      }
    }
    unsigned sum_f = 0;
    for (auto k = 0U; k < noMachines - 1; k++) {
      sum_f += F(noJobs - 1, k);
    }
    completionTimes[noJobs - 1] = sum_f + stats.machineProcTime(0);
    for (int j = static_cast<int>(noJobs) - 2; j >= 0; j--) {
      const auto p_jp1_m = fspData.pt(perm[j + 1], noMachines - 1);
      completionTimes[j] = completionTimes[j + 1] - p_jp1_m;
    }

    // backward pass calculation
    // for (int k = 0; k < noMachines - 1; k++) {
    //   E(noJobs - 1, k) = fspData.pt(perm[noJobs - 1], k);
    // }
    // for (int j = noJobs - 2; j >= 0; j--) {
    //   for (int k = 0; k < noMachines - 1; k++) {
    //     const auto p_j_k = fspData.pt(perm[j], k);
    //     const auto p_j_kp1 = fspData.pt(perm[j], k + 1);
    //     const auto E_jp1_k = E(j + 1, k);
    //     E(j, k) = std::max(E_jp1_k - p_j_kp1, 0) + p_j_k;
    //   }
    // }
    // int sum_f = 0;
    // for (int k = 0; k < noMachines - 1; k++) {
    //   sum_f += E(0, k);
    // }
    // completionTimes[0] = sum_f + fspData.pt(0, noMachines - 1);
    // for (int j = 0; j < noJobs - 1; j++) {
    //   completionTimes[j + 1] = completionTimes[j] + fspData.pt(j + 1,
    //   noMachines - 1);
    // }
  }
};