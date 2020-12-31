#pragma once

#include "Schedule.hpp"
#include "Instance.hpp"
#include "InstanceStatistics.hpp"

namespace fsp {

class NoIdleNeighborEvalCompiler
{
  class NoIdleFSPNeighborEvalCache
  {
    const Instance &instance;
    Schedule compiledCache;
    using job_t = unsigned short;

    std::vector<job_t> _F;
    std::vector<job_t> _E;
    std::vector<job_t> _Ff;

    [[nodiscard]] auto pt(unsigned j, int m) -> job_t { return instance.pt(j, m); }

  public:
    explicit NoIdleFSPNeighborEvalCache(const Instance &instance)
      : instance(instance),
        _F(instance.noJobs() * instance.noMachines(), 0),
        _E(instance.noJobs() * instance.noMachines(), 0),
        _Ff(instance.noJobs() * instance.noMachines(), 0) {}

    auto F(int j, int m) -> job_t & { return _F[m * instance.noJobs() + j]; }
    auto E(int j, int m) -> job_t & { return _E[m * instance.noJobs() + j]; }
    auto Ff(int j, int m) -> job_t & { return _Ff[m * instance.noJobs() + j]; }

    [[nodiscard]] auto F(int j, int m) const -> job_t
    {
      return _F[m * instance.noJobs() + j];
    }
    [[nodiscard]] auto E(int j, int m) const -> job_t
    {
      return _E[m * instance.noJobs() + j];
    }
    [[nodiscard]] auto Ff(int j, int m) const -> job_t
    {
      return _Ff[m * instance.noJobs() + j];
    }

    void compile(const Schedule &partialPerm)
    {
      const int noJobs = static_cast<int>(partialPerm.size());
      const int noMachines = static_cast<int>(instance.noMachines());

      // Calculate F(p^E_j, k, k+1)
      for (int k = 0; k < noMachines - 1; k++) {
        F(0, k) = pt(partialPerm[0], k + 1);
      }
      for (int j = 1; j < noJobs; j++) {
        for (int k = 0; k < noMachines - 1; k++) {
          const auto p_j_k = pt(partialPerm[j], k);
          const auto p_j_kp1 = pt(partialPerm[j], k + 1);
          const auto F_jm1_k = F(j - 1, k);
          F(j, k) = std::max(F_jm1_k - p_j_k, 0) + p_j_kp1;
        }
      }

      // Calculate E(p^E_j, k, k+1)
      for (int k = 0; k < noMachines - 1; k++) {
        E(noJobs - 1, k) = pt(partialPerm[noJobs - 1], k);
      }
      for (int j = noJobs - 2; j >= 0; j--) {
        for (int k = 0; k < noMachines - 1; k++) {
          const auto p_j_k = pt(partialPerm[j], k);
          const auto p_j_kp1 = pt(partialPerm[j], k + 1);
          const auto E_jp1_k = E(j + 1, k);
          E(j, k) = std::max(E_jp1_k - p_j_kp1, 0) + p_j_k;
        }
      }

      // Calculate F(p^F_j, k, k+1)
      for (int k = 0; k < noMachines - 1; k++) {
        Ff(noJobs - 1, k) = pt(partialPerm[noJobs - 1], k + 1);
      }
      for (int j = noJobs - 2; j >= 0; j--) {
        for (int k = 0; k < noMachines - 1; k++) {
          const auto p_j_kp1 = pt(partialPerm[j], k + 1);
          const auto E_jp1_k = E(j + 1, k);
          const auto F_jp1_k = Ff(j + 1, k);

          Ff(j, k) = std::max(p_j_kp1 - E_jp1_k, 0) + F_jp1_k;
        }
      }
    }
  };

  const Instance &instance;
  const InstanceStatistics stats;
  std::vector<NoIdleFSPNeighborEvalCache> caches;
  std::vector<int> _Ct;

public:
  explicit NoIdleNeighborEvalCompiler(const Instance &instance)
    : instance(instance),
      stats(instance),
      _Ct(instance.noJobs(), 0)
  {
    for (unsigned i = 0; i < instance.noJobs(); i++) {
      caches.emplace_back(instance);
    }
  }

  // [[nodiscard]] auto noJobs() -> int { return instance.noJobs(); }

  void compile(const Schedule &perm,
    const std::pair<unsigned, unsigned> &move)
  {
    const auto &t = move.first;
    const auto &h = move.second;

    Schedule partialPerm = perm;
    partialPerm.erase(partialPerm.begin() + t);

    caches[t].compile(partialPerm);
    const auto &cache = caches[t];

    const int noMachines = static_cast<int>(instance.noMachines());

    // Calculate F(pEh, k, k+1) appending job h
    std::vector<int> FpEh(noMachines - 1, 0);
    if (h == 0) {
      for (int k = 0; k < noMachines - 1; k++) {
        FpEh[k] = instance.pt(perm[t], k + 1);
      }

    } else {
      for (int k = 0; k < noMachines - 1; k++) {
        const auto p_h_k = static_cast<int>(instance.pt(perm[t], k));
        const auto p_h_kp1 = static_cast<int>(instance.pt(perm[t], k + 1));
        const auto F_hm1_k = static_cast<int>(cache.F(static_cast<int>(h) - 1, k));
        FpEh[k] = std::max(F_hm1_k - p_h_k, 0) + p_h_kp1;
      }
    }

    // Calculate F(p, k, k+1) appending job h
    std::vector<int> Fp(noMachines - 1, 0);
    for (int k = 0; k < noMachines - 1; k++) {
      const auto Fe_k = FpEh[k];
      const auto E_h_k = cache.E(h, k);
      const auto Ff_h_k = cache.Ff(h, k);
      Fp[k] = std::max(Fe_k - E_h_k, 0) + Ff_h_k;
    }

    Schedule newPerm = partialPerm;
    newPerm.insert(newPerm.begin() + h, perm[t]);
    _Ct[perm.size() - 1] =
      std::accumulate(begin(Fp), end(Fp), 0) + stats.machineProcTime(0);

    for (int j = static_cast<int>(newPerm.size()) - 2; j >= 0; j--) {
      _Ct[j] = _Ct[j + 1] - instance.pt(newPerm[j + 1], noMachines - 1);
    }
  }

  [[nodiscard]] auto compiledCompletionTime(int i) const -> int
  {
    return _Ct[i];
  }

  [[nodiscard]] auto sumCompletionTimes() const -> int
  {
    return std::accumulate(begin(_Ct), end(_Ct), 0);
  }
};

}// namespace fsp