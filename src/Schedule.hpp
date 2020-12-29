#pragma once

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <vector>
#include <numeric>
#include <cassert>

class Schedule
{
public:
  using difference_type = typename std::vector<unsigned>::difference_type;
  using size_type = typename std::vector<unsigned>::size_type;

  explicit Schedule(size_type size) : jobOrder(permutationOfSize(size))
  {
  }

  Schedule(std::initializer_list<unsigned> order) : jobOrder(order)
  {
    if (!isPermutation()) {
      throw std::runtime_error("Job order is not a valid permutation!");
    }
  }

  auto operator[](size_type index) -> unsigned &
  {
    return jobOrder[index];
  }

  auto operator[](size_type index) const -> const unsigned &
  {
    return jobOrder[index];
  }

  [[nodiscard]] auto size() const { return jobOrder.size(); }

private:
  std::vector<unsigned> jobOrder;

  static auto permutationOfSize(size_type size) -> std::vector<unsigned>
  {
    std::vector<unsigned> vec(size);
    std::iota(begin(vec), end(vec), 0);
    return vec;
  }

  auto isPermutation() -> bool
  {
    const auto permutation = permutationOfSize(jobOrder.size());
    return std::is_permutation(begin(jobOrder), end(jobOrder), begin(permutation));
  }
};