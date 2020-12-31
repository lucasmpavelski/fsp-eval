#pragma once

#include <ostream>
#include <vector>

#include "Instance.hpp"
#include "InstanceStatistics.hpp"
#include "EvalFunction.hpp"
#include "Schedule.hpp"

namespace fsp {

class NoWaitCompletionTimeCompiler
{
  const Instance &instance;
  const InstanceStatistics stats;
  std::vector<int> delayMatrix;

  [[nodiscard]] auto computeDelayMatrix() const -> std::vector<int>
  {
    const unsigned N = instance.noJobs();
    const unsigned M = instance.noMachines();
    const auto &p = instance.procTimesRef();
    std::vector<int> _delayMatrix(N * N);

    // See : A heuristic for no-wait flow shop scheduling (2013) Sagar U. Sapkal
    // & Dipak Laha for the computation of the delay matrix
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (i != j) {
          int max = 0;
          int idx = 0;
          for (int r = 1; r <= M; r++) {
            int s = 0;
            for (int h = 1; h < r; h++) {
              s += p[h * N + i];
            }
            for (int h = 0; h < r - 1; h++) {
              s -= p[h * N + j];
            }
            if (s < 0) {
              s = 0;
            }
            if (s > max) {
              max = s;
              idx = r;
            }
          }
          _delayMatrix[i * N + j] = p[0 * N + i] + max;
        } else {
          _delayMatrix[i * N + j] = 0;
        }
      }
    }
    return _delayMatrix;
  }

public:
  explicit NoWaitCompletionTimeCompiler(const Instance &instance)
    : instance{ instance }, stats{ instance }, delayMatrix{ computeDelayMatrix() } {}

  void compile(const Schedule &_fsp, std::vector<unsigned> &Ct)
  {
    const unsigned N = instance.noJobs();
    const unsigned _N = _fsp.size();

    int delay = 0;
    Ct[0] = stats.jobProcTime(_fsp[0]);

    for (int i = 1; i < _N; i++) {
      delay += delayMatrix[_fsp[i - 1] * N + _fsp[i]];
      Ct[i] = delay + stats.jobProcTime(_fsp[i]);
    }
  }

  [[nodiscard]] auto delay(int i, int j) const -> int
  {
    return delayMatrix[i * instance.noJobs() + j];
  }
};

}// namespace fsp