#pragma once

#include <vector>

#include "Schedule.hpp"
#include "Instance.hpp"
#include "EvalFunction.hpp"
#include "PermutationCompiler.hpp"

namespace fsp {

class PermutationEvalFunction : virtual public EvalFunction
{
  PermutationCompiler compiler;

public:
  explicit PermutationEvalFunction(const Instance &instance) : compiler{ instance } {}

  [[nodiscard]] auto type() const -> Type final { return Type::PERMUTATION; }

protected:
  void compileCompletionTimes(const Schedule &perm, std::vector<unsigned> &cts) override
  {
    compiler.compile(perm, cts);
  }
};

}// namespace fsp