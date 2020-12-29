#pragma once

#include <vector>

#include "Schedule.hpp"
#include "FSPData.hpp"
#include "EvalFunction.hpp"
#include "PermutationCompiler.hpp"

class PermutationEvalFunction : virtual public EvalFunction {
  PermutationCompiler compiler;

 public:
  explicit PermutationEvalFunction(const FSPData& fspData) : compiler{fspData} {}

  [[nodiscard]] auto type() const -> std::string final { return "PERM"; }

 protected:
  void compileCompletionTimes(const Schedule& perm, std::vector<unsigned>& cts) override {
    compiler.compile(perm, cts);
  }
};