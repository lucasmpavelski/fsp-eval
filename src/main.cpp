#include <functional>
#include <iostream>
#include <iostream>

#include <spdlog/spdlog.h>
#include <docopt/docopt.h>
#include <fmt/ostream.h>

#include "FSPData.hpp"


int main(int  /*argc*/, const char ** /*argv*/)
{
  std::default_random_engine rng;
  const unsigned no_jobs = 20U;
  const unsigned no_machines = 5U;
  const int max = 99;
  FSPData data(no_jobs, no_machines, rng, max);
  fmt::print(std::cerr, "{}", data);
}
