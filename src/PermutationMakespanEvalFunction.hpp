#pragma once

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "Instance.hpp"
#include "PermutationEvalFunction.hpp"
#include "MakespanEvalFunction.hpp"
#include "Schedule.hpp"

namespace fsp {

class PermutationMakespanEvalFunction : public PermutationEvalFunction
  , public MakespanEvalFunction
{
public:
  explicit PermutationMakespanEvalFunction(const Instance &instance)
    : EvalFunction{ instance }, PermutationEvalFunction{ instance } {}
};

}// namespace fsp