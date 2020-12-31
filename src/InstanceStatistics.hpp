#pragma once

#include <vector>

#include "Instance.hpp"

namespace fsp {

class InstanceStatistics
{
  std::vector<unsigned> jobProcTimes, machineProcTimes;
  unsigned max_ct = 0;

  void computeJobProcTimes(const Instance &instance)
  {
    for (unsigned i = 0; i < instance.noJobs(); i++) {
      for (unsigned j = 0; j < instance.noMachines(); j++) {
        jobProcTimes[i] += instance.pt(i, j);
      }
    }
  }

  void computeMachineProcTimes(const Instance &instance)
  {
    for (unsigned i = 0; i < instance.noJobs(); i++) {
      for (unsigned j = 0; j < instance.noMachines(); j++) {
        machineProcTimes[j] += instance.pt(i, j);
      }
    }
  }

  void computeMaxCT(const Instance &instance)
  {
    for (unsigned i = 0; i < instance.noJobs(); i++) {
      for (unsigned j = 0; j < instance.noMachines(); j++) {
        max_ct += instance.pt(i, j);
      }
    }
  }

public:
  InstanceStatistics() = default;

  explicit InstanceStatistics(const Instance &instance) : jobProcTimes(instance.noJobs(), 0U),
                                                          machineProcTimes(instance.noMachines(), 0U)
  {
    computeJobProcTimes(instance);
    computeMachineProcTimes(instance);
    computeMaxCT(instance);
  }

  [[nodiscard]] auto maxCT() const -> unsigned { return max_ct; }

  auto machineProcTimesRef() -> std::vector<unsigned> & { return machineProcTimes; }
  [[nodiscard]] auto machineProcTimesRef() const -> const std::vector<unsigned> &
  {
    return machineProcTimes;
  }
  [[nodiscard]] auto machineProcTime(const unsigned m) const
  {
    return machineProcTimes[m];
  }

  auto jobProcTimesRef() -> std::vector<unsigned> & { return jobProcTimes; }
  [[nodiscard]] auto jobProcTimesRef() const -> const std::vector<unsigned> &
  {
    return jobProcTimes;
  }
  [[nodiscard]] auto jobProcTime(const unsigned j) const
  {
    return jobProcTimes[j];
  }
};

}// namespace fsp