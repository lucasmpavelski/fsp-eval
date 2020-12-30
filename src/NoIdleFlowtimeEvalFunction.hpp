#pragma once

#include "EvalFunction.hpp"
#include "FSPData.hpp"
#include "NoIdleEvalFunction.hpp"
#include "FlowtimeEvalFunction.hpp"

class NoIdleFlowtimeEvalFunction : public FlowtimeEvalFunction, public NoIdleEvalFunction {
 public:
  explicit NoIdleFlowtimeEvalFunction(const FSPData& fspData)
      : EvalFunction{fspData}, NoIdleEvalFunction{fspData} {}
};
