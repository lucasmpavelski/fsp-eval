#include <functional>
#include <iostream>
#include <iostream>

#include "Instance.hpp"


int main(int  /*argc*/, const char ** /*argv*/)
{
  using namespace fsp;
  std::default_random_engine rng;
  const unsigned no_jobs = 20U;
  const unsigned no_machines = 5U;
  const int max = 99;
  Instance data(no_jobs, no_machines, rng, max);
}
