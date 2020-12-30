#pragma once

#include "MakespanEvalFunction.hpp"
#include "NoWaitEvalFunction.hpp"


class NoWaitMakespanEvalFunction : public NoWaitEvalFunction
  , public MakespanEvalFunction
{
public:
  explicit NoWaitMakespanEvalFunction(const FSPData &fspData)
    : EvalFunction{ fspData }, NoWaitEvalFunction{ fspData } {}
};
