#pragma once

#include "core/config.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace engine::core {
class App final {
public:
  App();

  void Run();

private:
  void initWindow(const WindowConfig &window_cfg);

  sf::RenderWindow window_;
};
} // namespace engine::core