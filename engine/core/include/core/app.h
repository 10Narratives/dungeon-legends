#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace engine::core {
class App final {
public:
  App();

  void Run();

private:
  sf::RenderWindow window_;
};
} // namespace engine::core