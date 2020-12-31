#pragma once

#include "MakespanEvalFunction.hpp"
#include "NoWaitEvalFunction.hpp"

namespace fsp {

class NoWaitMakespanEvalFunction : public NoWaitEvalFunction
  , public MakespanEvalFunction
{
public:
  explicit NoWaitMakespanEvalFunction(const Instance &instance)
    : EvalFunction{ instance }, NoWaitEvalFunction{ instance } {}
};

}// namespace fsp