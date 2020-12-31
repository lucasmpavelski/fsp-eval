#pragma once

#include "Schedule.hpp"
#include <utility>

namespace fsp {

class Neighbor
{
  int first;
  int second;

public:
  Neighbor(int first, int second) : first(first), second(second) {}

  [[nodiscard]] std::pair<int, int> firstSecond() const
  {
    return { first, second };
  }

  [[nodiscard]] auto move(const Schedule &schedule) const -> Schedule
  {
    Schedule movedSchedule(schedule);
    if (first == second) {
      return movedSchedule;
    }
    auto begin = std::begin(movedSchedule);
    if (first < second) {
      std::rotate(begin + first, begin + first + 1, begin + second + 1);
    } else {
      std::rotate(begin + second, begin + first, begin + first + 1);
    }
    return movedSchedule;
  }
};

}// namespace fsp