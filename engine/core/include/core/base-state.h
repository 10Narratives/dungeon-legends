#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <cstddef>
#include <functional>
#include <string>

#include "core/state-manager.h"

namespace engine::core {

class BaseState {
 public:
  BaseState() = default;

  virtual void HandleInput(sf::RenderWindow& window) const = 0;
  virtual void Update(sf::Time delta_time) = 0;
  virtual void Render(sf::RenderWindow& window) const = 0;

  struct Hash final {
   public:
    [[nodiscard]] std::size_t operator()(const BaseState& state) const { return std::hash<std::string>()(state.name_); }
  };

 private:
  std::string name_;
  // StateManager& state_manager_;
};

}  // namespace engine::core