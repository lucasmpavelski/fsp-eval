#pragma once

#include "Instance.hpp"
#include "PermutationEvalFunction.hpp"
#include "FlowtimeEvalFunction.hpp"

namespace fsp {

class PermutationFlowtimeEvalFunction : public PermutationEvalFunction
  , public FlowtimeEvalFunction
{
public:
  explicit PermutationFlowtimeEvalFunction(const Instance &instance)
    : EvalFunction{ instance }, PermutationEvalFunction{ instance } {}
};

}// namespace fsp