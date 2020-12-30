#pragma once

#include <memory>

#include "EvalFunction.hpp"
#include "FSPData.hpp"
#include "Objective.hpp"
#include "Type.hpp"

#include "PermutationMakespanEvalFunction.hpp"
#include "PermutationFlowtimeEvalFunction.hpp"
#include "NoIdleMakespanEvalFunction.hpp"
#include "NoIdleFlowtimeEvalFunction.hpp"
#include "NoWaitMakespanEvalFunction.hpp"
#include "NoWaitFlowtimeEvalFunction.hpp"


class EvalFunctionFactory {
public:
  static std::unique_ptr<EvalFunction> build(Type type, Objective objective, const FSPData& data) {
    switch (objective) {
        case Objective::MAKESPAN:
            switch (type) {
                case Type::PERMUTATION:
                    return std::make_unique<PermutationMakespanEvalFunction>(data);
                case Type::NOIDLE:
                    return std::make_unique<NoIdleMakespanEvalFunction>(data);
                case Type::NOWAIT:
                    return std::make_unique<NoWaitMakespanEvalFunction>(data);
            }
        case Objective::FLOWTIME:
            switch (type) {
                case Type::PERMUTATION:
                    return std::make_unique<PermutationFlowtimeEvalFunction>(data);
                case Type::NOIDLE:
                    return std::make_unique<NoIdleFlowtimeEvalFunction>(data);
                case Type::NOWAIT:
                    return std::make_unique<NoWaitFlowtimeEvalFunction>(data);
            }
    }
  }
};