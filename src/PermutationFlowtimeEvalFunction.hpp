#pragma once

#include "FSPData.hpp"
#include "PermutationEvalFunction.hpp"
#include "FlowtimeEvalFunction.hpp"


class PermutationFlowtimeEvalFunction : public PermutationEvalFunction, public FlowtimeEvalFunction {
 public:
  explicit PermutationFlowtimeEvalFunction(const FSPData& fspData)
      : EvalFunction{fspData}, PermutationEvalFunction{fspData} {}
};
