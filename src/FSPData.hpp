#pragma once

#include <iomanip>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <cassert>

struct FSPData
{
private:
  void init()
  {
    total_job_proc_times.resize(no_jobs);
    total_machine_proc_times.resize(no_machines);
    std::fill(total_job_proc_times.begin(), total_job_proc_times.end(), 0);
    std::fill(total_machine_proc_times.begin(), total_machine_proc_times.end(), 0);
    max_ct = 0;
    for (unsigned i = 0; i < no_jobs; i++) {
      for (unsigned j = 0; j < no_machines; j++) {
        total_job_proc_times[i] += pt(i, j);
      }
    }
    for (unsigned i = 0; i < no_machines; i++) {
      for (unsigned j = 0; j < no_jobs; j++) {
        total_machine_proc_times[i] += pt(j, i);
      }
    }
    max_ct = static_cast<unsigned>(std::accumulate(total_job_proc_times.begin(),
      total_job_proc_times.end(),
      0));
  }

  using ivec = std::vector<int>;
  unsigned no_jobs{ 0 }, no_machines{ 0 }, max_ct{ 0 };
  ivec proc_times, total_job_proc_times, total_machine_proc_times;

public:
  explicit FSPData(const std::string &filename)
  {
    std::ifstream inputFile(filename, std::ios::in);
    if (!inputFile) {
      throw std::runtime_error("Instance file " + filename + " not found!");
    }
    inputFile >> no_jobs;
    inputFile >> no_machines;
    proc_times.resize(no_jobs * no_machines);
    for (unsigned i = 0; i < no_jobs; i++) {
      for (unsigned j = 0; j < no_machines; j++) {
        inputFile >> pt(i, j);
      }
    }
    init();
  }

  template<class RNG>
  FSPData(unsigned no_jobs_, unsigned no_machines_, RNG &rng, int max)
    : no_jobs{ no_jobs_ },
      no_machines{ no_machines_ },
      total_job_proc_times(no_jobs_),
      total_machine_proc_times(no_machines_)
  {
    assert(max >= 1);
    using std::begin;
    using std::end;
    proc_times.resize(no_jobs * no_machines);
    std::uniform_int_distribution<int> dist(1U, max);
    std::generate(begin(proc_times), end(proc_times), [&]() { return dist(rng) + 1; });
    init();
  }

  FSPData(const std::vector<int> &pts, unsigned no_jobs_, bool jobsPerMachines)
    : no_jobs{ no_jobs_ },
      no_machines{ static_cast<unsigned>(pts.size() / no_jobs) },
      proc_times(pts),
      total_job_proc_times(no_jobs_),
      total_machine_proc_times(no_machines)
  {
    for (unsigned j = 0; j < no_jobs; j++) {
      for (unsigned m = 0; m < no_machines; m++) {
        unsigned idx = j * no_machines + m;
        if (jobsPerMachines) {
          idx = m * no_machines + j;
        }
        pt(j, m) = pts[idx];
      }
    }
    init();
  }

  FSPData(const std::vector<int> &pts, unsigned no_jobs_)
    : FSPData{ pts, no_jobs_, false } {};

  friend auto operator<<(std::ostream &o, const FSPData &d) -> std::ostream &
  {
    o << "FSPData:\n"//
      << "  no_jobs: " << d.no_jobs << '\n'//
      << "  no_machines: " << d.no_machines << '\n';//
    const double scale = 1.0 / std::log(10);
    int w = int(std::log(d.max_ct) * scale) + 2;
    auto sw = std::setw(w);
    int pad = w + w * (static_cast<int>(d.no_jobs) - 1) - 1;
    o << std::left << std::setw(pad) << " " << sw << "job" << '\n'
      << sw << "mac";
    for (unsigned j = 0; j < d.no_jobs; j++) {
      o << sw << j;
    }
    o << "sum\n";
    for (unsigned i = 0; i < d.no_machines; i++) {
      o << sw << i;
      for (unsigned j = 0; j < d.no_jobs; j++) {
        o << sw << d.proc_times[i * d.no_jobs + j];
      }
      o << '+' << sw << d.total_machine_proc_times[i] << '\n';
    }
    o << sw << "sum";
    for (unsigned j = 0; j < d.no_jobs; j++) {
      o << "+" << std::setw(w - 1) << d.total_job_proc_times[j];
    }
    o << "+" << std::setw(w - 1) << d.max_ct;
    return o;
  }

  [[nodiscard]] auto noJobs() const -> unsigned { return no_jobs; }
  [[nodiscard]] auto noMachines() const -> unsigned { return no_machines; }
  [[nodiscard]] auto maxCT() const -> unsigned { return max_ct; }

  auto machineProcTimesRef() -> ivec & { return total_machine_proc_times; }
  [[nodiscard]] auto machineProcTimesRef() const -> const ivec &
  {
    return total_machine_proc_times;
  }
  [[nodiscard]] auto machineProcTime(const unsigned m) const
  {
    return total_machine_proc_times[m];
  }

  auto jobProcTimesRef() -> ivec & { return total_job_proc_times; }
  [[nodiscard]] auto jobProcTimesRef() const -> const ivec &
  {
    return total_job_proc_times;
  }
  [[nodiscard]] auto jobProcTime(const unsigned j) const
  {
    return total_job_proc_times[j];
  }

  [[nodiscard]] auto procTimesRef() const -> const ivec & { return proc_times; }
  [[nodiscard]] auto pt(const ivec::size_type j, const ivec::size_type m) const
    -> int
  {
    return proc_times[m * no_jobs + j];
  }

  auto procTimesRef() -> ivec & { return proc_times; }
  auto pt(const unsigned j, const unsigned m) -> int &
  {
    return proc_times[m * no_jobs + j];
  }

  [[nodiscard]] auto partialSumOnAdjacentMachines(unsigned job, unsigned i, unsigned h) const
    -> int
  {
    int sm = 0;
    for (unsigned j = i; j <= h; j++) {
      sm += pt(job, j);
    }
    return sm;
  }
};
