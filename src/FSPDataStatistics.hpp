#include <vector>

#include "FSPData.hpp"

class FSPDataStatistics
{
  std::vector<unsigned> jobProcTimes, machineProcTimes;
  unsigned max_ct = 0;

  void computeJobProcTimes(const FSPData &fspData)
  {
    for (unsigned i = 0; i < fspData.noJobs(); i++) {
      for (unsigned j = 0; j < fspData.noMachines(); j++) {
        jobProcTimes[i] += fspData.pt(i, j);
      }
    }
  }

  void computeMachineProcTimes(const FSPData &fspData)
  {
    for (unsigned i = 0; i < fspData.noJobs(); i++) {
      for (unsigned j = 0; j < fspData.noMachines(); j++) {
        machineProcTimes[j] += fspData.pt(i, j);
      }
    }
  }

  void computeMaxCT(const FSPData &fspData)
  {
    for (unsigned i = 0; i < fspData.noJobs(); i++) {
      for (unsigned j = 0; j < fspData.noMachines(); j++) {
        max_ct += fspData.pt(i, j);
      }
    }
  }

public:
  FSPDataStatistics() = default;

  explicit FSPDataStatistics(const FSPData &fspData) : jobProcTimes(fspData.noJobs(), 0U),
                                                       machineProcTimes(fspData.noMachines(), 0U)
  {
    computeJobProcTimes(fspData);
    computeMachineProcTimes(fspData);
    computeMaxCT(fspData);
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