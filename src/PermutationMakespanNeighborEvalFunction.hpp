#pragma once

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "Neighbor.hpp"
#include "Schedule.hpp"
#include "Instance.hpp"
#include "EvalFunction.hpp"

namespace fsp {

class PermutationMakespanNeighborEvalFunction
{

  struct CompiledSchedule
  {
  private:
    using ivec = std::vector<int>;
    const Instance &instance;
    ivec e_times, q_times, f_times, makespan;
    Schedule compiledSolution;

  public:
    explicit CompiledSchedule(const Instance &instance)
      : instance(instance),
        e_times((instance.noJobs() + 1) * (instance.noMachines() + 1)),
        q_times((instance.noJobs() + 1) * (instance.noMachines() + 2)),
        f_times((instance.noJobs() + 1) * (instance.noMachines() + 1)),
        makespan(instance.noJobs()),
        compiledSolution(0)
    {
      const unsigned no_jobs = instance.noJobs();
      const unsigned no_machines = instance.noMachines();
      e_(0, 0) = 0;
      for (int i = 1; i <= no_machines; i++) {
        e_(0U, i) = 0;
      }
      for (int i = 1; i <= no_jobs; i++) {
        e_(i, 0) = 0;
      }
      q_(no_jobs, no_machines) = 0;
      for (auto j = no_machines; j >= 1; j--) {
        q_(no_jobs, j) = 0;
      }
      for (auto i = no_jobs - 1; i >= 1; i--) {
        q_(i, no_machines + 1) = 0;
      }
      for (int i = 0; i <= no_jobs; i++) {
        f_(i, 0) = 0;
      }
    }

    inline auto e_(const unsigned j, const unsigned m) -> int &
    {
      return e_times[m * (instance.noJobs() + 1) + j];
    }

    inline auto q_(const unsigned j, const unsigned m) -> int &
    {
      return q_times[m * (instance.noJobs() + 1) + j];
    }

    inline auto f_(const unsigned j, const unsigned m) -> int &
    {
      return f_times[m * (instance.noJobs() + 1) + j];
    }

    void compile(const Schedule &seq)
    {
      compile(seq, 0);
    }

    void compile(const Schedule &seq, int from)
    {
      const auto no_jobs = instance.noJobs();
      const auto no_machines = instance.noMachines();
      const auto seq_size = static_cast<int>(seq.size());

      for (int i = from + 1; i <= seq_size - 1; i++) {
        auto seq_i = seq[i - 1];
        for (int j = 1; j <= no_machines; j++) {
          const auto pt = static_cast<int>(instance.pt(seq_i, j - 1));
          e_(i, j) = std::max(e_(i, j - 1), e_(i - 1, j)) + pt;
        }
      }

      for (int i = no_jobs; i >= seq_size - 1; i--) {
        for (int j = no_machines; j >= 1; j--) {
          q_(i, j) = 0;
        }
      }
      for (int i = seq_size - 1; i >= 1; i--) {
        auto seq_i = seq[i - 1];
        for (int j = no_machines; j >= 1; j--) {
          const auto pt = static_cast<int>(instance.pt(seq_i, j - 1));
          q_(i, j) = std::max(q_(i, j + 1), q_(i + 1, j)) + pt;
        }
      }
      for (int i = 1; i <= seq_size; i++) {
        auto seq_k = seq[seq_size - 1];
        for (int j = 1; j <= no_machines; j++) {
          const auto pt = static_cast<int>(instance.pt(seq_k, j - 1));
          f_(i, j) = std::max(f_(i, j - 1), e_(i - 1, j)) + pt;
        }
      }

      std::fill(makespan.begin(), makespan.end(), 0);
      for (int i = 1; i <= seq_size; i++) {
        for (int j = 1; j <= no_machines; j++) {
          int c_ij = f_(i, j) + q_(i, j);
          makespan[i - 1] = std::max(makespan[i - 1], c_ij);
        }
      }
    }

    auto getMakespan(const Schedule &sol, const int first, const int second) -> int
    {
      auto mPtr = std::mismatch(compiledSolution.begin(), compiledSolution.end(), sol.begin(), sol.end());
      int from = std::distance(sol.begin(), mPtr.second);

      if (mPtr.second != sol.end() || sol.size() != compiledSolution.size()) {
        Schedule perm_i = sol;
        std::rotate(perm_i.begin() + first, perm_i.begin() + first + 1, perm_i.end());

        compile(perm_i, std::max(0, from - 1));
        compiledSolution = sol;
      }
      return makespan[second];
    }
  };

  std::vector<CompiledSchedule> compiledSchedules;

public:
  explicit PermutationMakespanNeighborEvalFunction(const Instance &instance) : compiledSchedules{}
  {
    for (unsigned i = 0; i < instance.noJobs(); i++) {
      compiledSchedules.emplace_back(instance);
    }
  }

  auto operator()(const Schedule &sol, const Neighbor &ngh) -> double
  {
    auto firstSecond = ngh.firstSecond();
    auto &cache = compiledSchedules[firstSecond.first];
    return cache.getMakespan(sol, firstSecond.first, firstSecond.second);
  }
};

}// namespace fsp