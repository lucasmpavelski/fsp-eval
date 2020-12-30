#pragma once

#include <ostream>
#include <string>
#include <exception>

enum class Objective {
  MAKESPAN,
  FLOWTIME
};

inline auto asString(const Objective &objective) -> std::string
{
  switch (objective) {
  case Objective::MAKESPAN:
    return "makespan";
  case Objective::FLOWTIME:
    return "flowtime";
  }
}

template<class T>
auto fromString(const std::basic_string_view<T> &str) -> Objective
{
  if (str == "makespan") {
    return Objective::MAKESPAN;
  }
  if (str == "flowtime") {
    return Objective::FLOWTIME;
  }
  throw std::invalid_argument("Unkown objective " + str);
}

template<class T>
auto operator<<(std::basic_ostream<T> &os, const Objective &objective) -> std::basic_ostream<T> &
{
  return os << asString(objective);
}
