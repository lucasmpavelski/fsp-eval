#pragma once

#include "Schedule.hpp"
#include "FSPData.hpp"
#include "EvalFunction.hpp"
#include "NoIdleCompletionTimesCompiler.hpp"


class NoIdleEvalFunction : public virtual EvalFunction
{
  NoIdleCompletionTimesCompiler compiler;

public:
  explicit NoIdleEvalFunction(const FSPData &data) : compiler(data) {}

  [[nodiscard]] auto type() const -> std::string override { return "NOIDLE"; }

protected:
  void compileCompletionTimes(const Schedule &sol, std::vector<unsigned> &ct) override
  {
    compiler.compile(sol, ct);
  }
};
