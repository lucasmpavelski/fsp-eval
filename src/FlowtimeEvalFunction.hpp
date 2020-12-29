#pragma once

#include "EvalFunction.hpp"

class FlowtimeEvalFunction : virtual public EvalFunction
{
public:
  FlowtimeEvalFunction() = default;

  auto operator()(const Schedule &perm) -> double override
  {
    compile(perm);
    auto begCT = std::begin(completionTimesRef());
    auto endCT = std::next(begCT, static_cast<Schedule::difference_type>(perm.size()));
    return std::accumulate(begCT, endCT, 0U);
  }

  [[nodiscard]] auto objective() const -> std::string override
  {
    return "MAKESPAN";
  }
};