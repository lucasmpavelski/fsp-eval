#pragma once

#include <ostream>
#include <exception>
#include <stdexcept>
#include <string_view>

namespace fsp {

enum class Type {
  PERMUTATION,
  NOWAIT,
  NOIDLE
};

inline auto asString(const Type &type) -> std::string
{
  switch (type) {
  case Type::PERMUTATION:
    return "permutation";
  case Type::NOWAIT:
    return "no-wait";
  case Type::NOIDLE:
    return "no-idle";
  }
}

template<class T>
auto fromString(const std::basic_string_view<T> &str) -> Type
{
  if (str == "permutation") {
    return Type::PERMUTATION;
  }
  if (str == "no-wait") {
    return Type::NOWAIT;
  }
  if (str == "no-idle") {
    return Type::NOIDLE;
  }
  throw std::invalid_argument("Unkown type " + str);
}

template<class T>
auto operator<<(std::basic_ostream<T> &os, const Type &type) -> std::basic_ostream<T> &
{
  return os << asString(type);
}

}// namespace fsp