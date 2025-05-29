#pragma once

#include "app/config.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace app {
class App final {
 public:
  explicit App(const app::Config& config);

  void run();

 private:
  void initializeWindow(const app::WindowConfig& win_cfg);

  sf::RenderWindow window_;
};
}  // namespace app
