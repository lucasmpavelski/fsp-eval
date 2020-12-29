#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include "FSPData.hpp"
#include "Schedule.hpp"

class EvalFunction
{
  FSPData fspData;
  std::vector<unsigned> compTimes;

public:
  explicit EvalFunction(FSPData fd) : fspData{ std::move(fd) }, compTimes(fspData.noJobs()) {}
  EvalFunction(const EvalFunction &) = default;
  EvalFunction(EvalFunction &&) = default;
  virtual ~EvalFunction() = default;
  EvalFunction &operator=(const EvalFunction &other) = default;
  EvalFunction &operator=(EvalFunction &&other) = default;

  [[nodiscard]] auto noJobs() const -> unsigned { return fspData.noJobs(); }
  [[nodiscard]] auto noMachines() const -> unsigned { return fspData.noMachines(); }
  [[nodiscard]] auto getData() const -> const FSPData & { return fspData; }
  [[nodiscard]] virtual auto type() const -> std::string = 0;
  [[nodiscard]] virtual auto objective() const -> std::string = 0;

  void printOn(std::ostream &o)
  {
    o << "FSPEval\n"
      << "  type: " << type() << '\n'
      << "  objective: " << objective() << '\n'
      << fspData;
  }

  virtual auto operator()(const Schedule& schedule) -> double = 0;

protected:
  auto completionTime(std::vector<int>::size_type i) -> unsigned & { return compTimes[i]; }
  auto completionTimesRef() -> std::vector<unsigned> & { return compTimes; }
  void compile(const Schedule &perm) { compileCompletionTimes(perm, compTimes); }

  virtual void compileCompletionTimes(const Schedule &schedule,
    std::vector<unsigned> &ct) = 0;
};



