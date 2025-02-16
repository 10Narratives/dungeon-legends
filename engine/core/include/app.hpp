#pragma once

#include "config.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace engine::core {
class Application final {
public:
  Application();

  void Run();

private:
  void initWindow(const WindowConfig &cfg);

  sf::RenderWindow window_;
};
} // namespace engine::core