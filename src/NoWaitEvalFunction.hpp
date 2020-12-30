#pragma once

#include "EvalFunction.hpp"
#include "NoWaitCompletionTimeCompiler.hpp"
#include "Schedule.hpp"

class NoWaitEvalFunction : virtual public EvalFunction {
  NoWaitCompletionTimeCompiler compiler;

 public:
  explicit NoWaitEvalFunction(const FSPData& fspData) : compiler{fspData} {}

  [[nodiscard]] auto type() const -> std::string final { return "NOWAIT"; }

  [[nodiscard]] auto delay(int i, int j) const -> int {
    return compiler.delay(i, j);
  }

  using EvalFunction::getData;
  auto printDelayMatrix(std::ostream& os) -> std::ostream& {
    for (int i = 0; i < getData().noJobs(); i++) {
      for (int j = 0; j < getData().noJobs(); j++) {
        os << delay(i, j) << ' ';
      }
      os << '\n';
    }
    return os;
  }

 protected:
  void compileCompletionTimes(const Schedule& perm, std::vector<unsigned>& ct) override {
    compiler.compile(perm, ct);
  }
};
