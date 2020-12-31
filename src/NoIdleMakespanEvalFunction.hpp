#pragma once

#include "EvalFunction.hpp"
#include "Instance.hpp"
#include "NoIdleEvalFunction.hpp"
#include "MakespanEvalFunction.hpp"

namespace fsp {

class NoIdleMakespanEvalFunction : public MakespanEvalFunction
  , public NoIdleEvalFunction
{
public:
  explicit NoIdleMakespanEvalFunction(const Instance &instance)
    : EvalFunction{ instance }, NoIdleEvalFunction{ instance } {}
};

}// namespace fsp