#pragma once

#include "Schedule.hpp"
#include "EvalFunction.hpp"

namespace fsp {

class MakespanEvalFunction : virtual public EvalFunction
{
public:
  MakespanEvalFunction() = default;

  auto operator()(const Schedule &perm) -> double override
  {
    compile(perm);
    return perm.size() == 0 ? 0 : completionTime(perm.size() - 1);
  }

  [[nodiscard]] auto objective() const -> Objective override
  {
    return Objective::MAKESPAN;
  }
};

}// namespace fsp