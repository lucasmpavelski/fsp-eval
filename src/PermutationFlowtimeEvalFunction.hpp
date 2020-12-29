#pragma once

#include "FSPData.hpp"
#include "PermutationEvalFunction.hpp"
#include "FlowtimeEvalFunction.hpp"


class PermFSPFlowtimeEval : public PermutationEvalFunction, public FlowtimeEvalFunction {
 public:
  explicit PermFSPFlowtimeEval(const FSPData& fspData)
      : EvalFunction{fspData}, PermutationEvalFunction{fspData} {}
};
