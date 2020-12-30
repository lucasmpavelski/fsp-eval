#pragma once

#include "EvalFunction.hpp"
#include "FSPData.hpp"
#include "NoIdleEvalFunction.hpp"
#include "MakespanEvalFunction.hpp"

class NoIdleMakespanEvalFunction : public MakespanEvalFunction, public NoIdleEvalFunction {
 public:
  explicit NoIdleMakespanEvalFunction(const FSPData& fspData)
      : EvalFunction{fspData}, NoIdleEvalFunction{fspData} {}
};
