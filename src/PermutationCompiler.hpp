#pragma once

#include <vector>

#include "FSPData.hpp"
#include "Schedule.hpp"

class PermutationCompiler {
  const FSPData& fspData;
  std::vector<unsigned> part_ct;
  std::vector<unsigned> cache;
  unsigned noJobs;

 public:
  explicit PermutationCompiler(const FSPData& fspData)
      : fspData{fspData}, part_ct(fspData.noJobs() * fspData.noMachines()), cache(fspData.noJobs()), noJobs(fspData.noJobs()) {}

  void compile(const Schedule& _fsp, std::vector<unsigned>& Ct) {
    const auto _N = static_cast<unsigned>(_fsp.size());
    const auto N = fspData.noJobs();
    const auto M = fspData.noMachines();
    const auto& p = fspData.procTimesRef();

    // std::cout << _fsp << '\n';

    /** extra **/
    // int idle = 0;
    // std::cout << "idle ";

    // int wait = 0;
    // std::cout << "wait ";
    /** extra **/

    part_ct[0 * N + 0] = p[0 * N + _fsp[0]];
    for (auto i = 1; i < _N; i++) {
      part_ct[0 * N + i] = part_ct[0 * N + i - 1] + p[0 * N + _fsp[i]];
    }

    for (auto j = 1; j < M; j++) {
      part_ct[j * N + 0] = part_ct[(j - 1) * N + 0] + p[j * N + _fsp[0]];
    }

    bool cachedJob = cache[0] == _fsp[0];
    for (auto i = 1; i < _N; i++) {
      unsigned pt_index = _fsp[i];
      if (cachedJob && cache[i] == pt_index) {
        continue;
      }
      cachedJob = false;
      cache[i] = pt_index;
      for (unsigned j = 1; j < M; j++) {
        int ct_jm1_m = part_ct[j * N + i - 1];
        int ct_j_mm1 = part_ct[(j - 1) * N + i];
        int pt_i = p[j * N + pt_index];
        part_ct[j * N + i] = 
          std::max(ct_jm1_m, ct_j_mm1) + pt_i;
      }
    }
    cache[0] = _fsp[0];



        /** extra **/
        // idle += std::max(part_ct[(j - 1) * N + i] - part_ct[j * N + i - 1],
        // 0); std::cout << '(' << i << ',' << j << ')' << std::max(part_ct[(j -
        // 1) * N + i] - part_ct[j * N + i - 1], 0) << ' ';
        /** extra **/

        /** extra **/
        // wait += std::max(part_ct[j * N + i - 1] - part_ct[(j - 1) * N + i] ,
        // 0); std::cout << '(' << i << ',' << j << ')' << std::max(part_ct[(j -
        // 1) * N + i] - part_ct[j * N + i - 1], 0) << ' ';
        /** extra **/

    /** extra **/
    // std::cout << "final idle " << idle << '\n';
    // std::cout << "final wait " << wait << '\n';
    /** extra **/

    auto fromCt = part_ct.begin() + (M - 1) * N;
    auto toCt = fromCt + _N;
    Ct.assign(fromCt, toCt);
  }
};