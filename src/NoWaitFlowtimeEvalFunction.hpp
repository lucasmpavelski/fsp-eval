#pragma once

#include "FlowtimeEvalFunction.hpp"
#include "NoWaitEvalFunction.hpp"

namespace fsp {

class NoWaitFlowtimeEvalFunction : public NoWaitEvalFunction
  , public FlowtimeEvalFunction
{
public:
  explicit NoWaitFlowtimeEvalFunction(const Instance &instance)
    : EvalFunction{ instance }, NoWaitEvalFunction{ instance } {}
};

}// namespace fsp
