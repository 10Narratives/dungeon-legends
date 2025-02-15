#pragma once

#include <memory>
#include <unordered_set>

#include "core/base-state.h"
namespace engine::core {

class StateManager final {
 public:
  StateManager() = default;

  [[nodiscard]] std::weak_ptr<BaseState> Current() const;

  void ChangeOn(const std::string& state_name);

 private:
  std::unordered_set<std::shared_ptr<BaseState>, BaseState::Hash> states_{};
  std::string curr_state_name_{};
};

}  // namespace engine::core