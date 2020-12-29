#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include "FSPData.hpp"
#include "FSPSchedule.hpp"

class FSPEvalFunction
{
  FSPData fspData;
  std::vector<unsigned> compTimes;

public:
  explicit FSPEvalFunction(FSPData fd) : fspData{ std::move(fd) }, compTimes(fspData.noJobs()) {}
  FSPEvalFunction(const FSPEvalFunction &) = default;
  FSPEvalFunction(FSPEvalFunction &&) = default;
  virtual ~FSPEvalFunction() = default;
  FSPEvalFunction &operator=(const FSPEvalFunction &other) = default;
  FSPEvalFunction &operator=(FSPEvalFunction &&other) = default;

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

  virtual auto operator()(const FSPSchedule& schedule) -> double = 0;

protected:
  auto completionTime(std::vector<int>::size_type i) -> unsigned & { return compTimes[i]; }
  auto completionTimesRef() -> std::vector<unsigned> & { return compTimes; }
  void compile(const FSPSchedule &perm) { compileCompletionTimes(perm, compTimes); }

  virtual void compileCompletionTimes(const FSPSchedule &schedule,
    std::vector<unsigned> &ct) = 0;
};

class FSPMakespanEval : virtual public FSPEvalFunction
{
public:
  FSPMakespanEval() = default;

  auto operator()(const FSPSchedule &perm) -> double override
  {
    compile(perm);
    return perm.size() == 0 ? 0 : completionTime(perm.size() - 1);
  }

  [[nodiscard]] auto objective() const -> std::string override
  {
    return "MAKESPAN";
  }
};

class FSPFlowtimeEval : virtual public FSPEvalFunction
{
public:
  FSPFlowtimeEval() = default;

  auto operator()(const FSPSchedule &perm) -> double override
  {
    compile(perm);
    auto begCT = std::begin(completionTimesRef());
    auto endCT = std::next(begCT, static_cast<FSPSchedule::difference_type>(perm.size()));
    return std::accumulate(begCT, endCT, 0U);
  }

  [[nodiscard]] auto objective() const -> std::string override
  {
    return "MAKESPAN";
  }
};
