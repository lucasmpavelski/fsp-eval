#pragma once

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <vector>
#include <numeric>
#include <cassert>

namespace fsp {

class Schedule
{
public:
  using difference_type = typename std::vector<unsigned>::difference_type;
  using size_type = typename std::vector<unsigned>::size_type;
  using iterator = typename std::vector<unsigned>::iterator;
  using const_iterator = typename std::vector<unsigned>::const_iterator;

  Schedule() = default;

  explicit Schedule(std::vector<unsigned> jobOrder) : jobOrder(std::move(jobOrder)) {}

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

  iterator begin() { return jobOrder.begin(); }

  [[nodiscard]] const_iterator begin() const
  {
    return jobOrder.cbegin();
  }

  iterator end() { return jobOrder.end(); }

  [[nodiscard]] const_iterator end() const
  {
    return jobOrder.cend();
  }

  auto erase(const_iterator first)
  {
    return jobOrder.erase(first);
  }

  auto erase(const_iterator first, const_iterator last)
  {
    return jobOrder.erase(first, last);
  }

  auto insert(const_iterator first, unsigned el)
  {
    return jobOrder.insert(first, el);
  }

private:
  std::vector<unsigned> jobOrder;

  static auto permutationOfSize(size_type size) -> std::vector<unsigned>
  {
    std::vector<unsigned> vec(size);
    std::iota(vec.begin(), vec.end(), 0);
    return vec;
  }

  auto isPermutation() -> bool
  {
    const auto permutation = permutationOfSize(jobOrder.size());
    return std::is_permutation(begin(), end(), permutation.begin());
  }
};

}// namespace fsp