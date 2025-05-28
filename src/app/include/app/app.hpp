#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace app {
class App final {
 public:
  App();

  void Run();

 private:
  sf::RenderWindow window_;
};
}  // namespace app
