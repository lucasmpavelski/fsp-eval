# automatically enable catch2 to generate ctest targets
if(CONAN_CATCH2_ROOT_DEBUG)
  include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
  include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()

add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC CONAN_PKG::catch2)
target_link_libraries(catch_main PRIVATE project_options)

add_executable(
  tests 
  InstanceTests.cpp
  InstanceStatisticsTests.cpp
  ScheduleTests.cpp
  PermutationMakespanEvalFunctionTests.cpp
  PermutationFlowtimeEvalFunctionTests.cpp
  NoIdleMakespanEvalFunctionTests.cpp
  NoIdleFlowtimeEvalFunctionTests.cpp
  NoWaitMakespanEvalFunctionTests.cpp
  NoWaitFlowtimeEvalFunctionTests.cpp
  PermutationMakespanNeighborEvalFunctionTests.cpp
  NoIdleMakespanNeighborEvalFunctionTests.cpp
  NoIdleFlowtimeNeighborEvalFunctionTests.cpp
  NoWaitMakespanNeighborEvalFuncionTests.cpp
  EvalFunctionFactoryTests.cpp
)
target_link_libraries(tests PRIVATE project_warnings project_options catch_main)

# automatically discover tests that are defined in catch based test files you can modify the unittests. TEST_PREFIX to
# whatever you want, or use different for different binaries
catch_discover_tests(
  tests
  TEST_PREFIX
  ""
  EXTRA_ARGS
  -s
  WORKING_DIRECTORY
  ${CMAKE_SOURCE_DIR})
