#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "core/config.h"
#include "core/state-manager.h"

namespace engine::core {
class App final {
 public:
  App();

  void Run();

 private:
  void initWindow(const WindowConfig &window_cfg);

  sf::RenderWindow window_;
  StateManager state_manager_;
};
}  // namespace engine::core