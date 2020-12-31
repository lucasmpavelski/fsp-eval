#pragma once

#include "EvalFunction.hpp"
#include "Instance.hpp"
#include "NoIdleEvalFunction.hpp"
#include "FlowtimeEvalFunction.hpp"

namespace fsp {

class NoIdleFlowtimeEvalFunction : public FlowtimeEvalFunction
  , public NoIdleEvalFunction
{
public:
  explicit NoIdleFlowtimeEvalFunction(const Instance &instance)
    : EvalFunction{ instance }, NoIdleEvalFunction{ instance } {}
};

}// namespace fsp