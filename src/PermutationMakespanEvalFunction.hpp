#pragma once

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "FSPData.hpp"
#include "PermutationEvalFunction.hpp"
#include "MakespanEvalFunction.hpp"
#include "Schedule.hpp"


class PermutationMakespanEvalFunction : public PermutationEvalFunction, public MakespanEvalFunction {
 public:
  explicit PermutationMakespanEvalFunction(const FSPData& fspData)
      : EvalFunction{fspData}, PermutationEvalFunction{fspData} {}
};
