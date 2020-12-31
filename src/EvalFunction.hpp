#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include "Instance.hpp"
#include "Schedule.hpp"
#include "Type.hpp"
#include "Objective.hpp"

namespace fsp {

class EvalFunction
{
  Instance instance;
  std::vector<unsigned> compTimes;

public:
  explicit EvalFunction(Instance fd) : instance{ std::move(fd) }, compTimes(instance.noJobs()) {}
  EvalFunction(const EvalFunction &) = default;
  EvalFunction(EvalFunction &&) = default;
  virtual ~EvalFunction() = default;
  EvalFunction &operator=(const EvalFunction &other) = default;
  EvalFunction &operator=(EvalFunction &&other) = default;

  [[nodiscard]] auto noJobs() const -> unsigned { return instance.noJobs(); }
  [[nodiscard]] auto noMachines() const -> unsigned { return instance.noMachines(); }
  [[nodiscard]] auto getData() const -> const Instance & { return instance; }
  [[nodiscard]] virtual auto type() const -> Type = 0;
  [[nodiscard]] virtual auto objective() const -> Objective = 0;

  void printOn(std::ostream &o)
  {
    o << "FSPEval\n"
      << "  type: " << type() << '\n'
      << "  objective: " << objective() << '\n'
      << instance;
  }

  virtual auto operator()(const Schedule &schedule) -> double = 0;

  friend auto operator==(const EvalFunction &lhs, const EvalFunction &rhs) -> bool
  {
    return lhs.objective() == rhs.objective() &&//
           lhs.type() == rhs.type() &&//
           lhs.getData() == rhs.getData();
  }

protected:
  auto completionTime(std::vector<int>::size_type i) -> unsigned & { return compTimes[i]; }
  auto completionTimesRef() -> std::vector<unsigned> & { return compTimes; }
  void compile(const Schedule &perm) { compileCompletionTimes(perm, compTimes); }

  virtual void compileCompletionTimes(const Schedule &schedule,
    std::vector<unsigned> &ct) = 0;
};

}// namespace fsp
