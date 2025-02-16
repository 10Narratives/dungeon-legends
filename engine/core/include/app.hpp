#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace engine::core {
class Application final {
public:
  Application();

  void Run();

private:
  sf::RenderWindow window_;
};
} // namespace engine::core