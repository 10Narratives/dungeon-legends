#include "app/app.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace app {
App::App() { window_.create(sf::VideoMode::getDesktopMode(), "Dungeon Legends"); }

void App::Run() {
  while (window_.isOpen()) {
    while (const auto& event = window_.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window_.close();
      }
    }

    window_.clear();
    window_.display();
  }
}
}  // namespace app
