#include <catch2/catch.hpp>
#include <stdexcept>
#include <vector>

#include "../src/Schedule.hpp"

using namespace fsp;

TEST_CASE("Create default ordered schedule", "[fsp]")
{
  Schedule schedule(3);

  REQUIRE(schedule[0] == 0);
  REQUIRE(schedule[1] == 1);
  REQUIRE(schedule[2] == 2);
}

TEST_CASE("Throws on invalid permutation", "[fsp]")
{
  REQUIRE_THROWS(Schedule({ 1, 2, 3 }));
}

class uncopyable_vector : public std::vector<unsigned> {
  public:
  using std::vector<unsigned>::vector;
  uncopyable_vector(uncopyable_vector&& other) = default;
  ~uncopyable_vector() = default;
  uncopyable_vector& operator=(uncopyable_vector&& other) = default;

  uncopyable_vector(const uncopyable_vector& other)  : vector(other) {
    throw std::runtime_error("copying is not allowed!");
  }
  uncopyable_vector& operator=(const uncopyable_vector&  other) {
    if (&other != this) {
      throw std::runtime_error("copying is not allowed!");
    }
    return *this;
  }
};

TEST_CASE("Can create schedule form vector without copy", "[fsp]")
{
  uncopyable_vector vec({0, 1, 2, 3});
  REQUIRE_NOTHROW(Schedule(std::move(vec)));
}
