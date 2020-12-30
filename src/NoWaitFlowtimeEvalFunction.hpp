#pragma once

#include "FlowtimeEvalFunction.hpp"
#include "NoWaitEvalFunction.hpp"


class NoWaitFlowtimeEvalFunction : public NoWaitEvalFunction
  , public FlowtimeEvalFunction
{
public:
  explicit NoWaitFlowtimeEvalFunction(const FSPData &fspData)
    : EvalFunction{ fspData }, NoWaitEvalFunction{ fspData } {}
};
