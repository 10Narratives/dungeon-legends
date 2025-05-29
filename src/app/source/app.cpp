#include "app/app.hpp"
#include "app/config.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace app {
App::App(const app::Config& config) {
  initializeWindow(config.getWindowConfig());
}

void App::initializeWindow(const app::WindowConfig& win_cfg) {
  window_.create(sf::VideoMode::getDesktopMode(), win_cfg.title);
  window_.setFramerateLimit(win_cfg.framerate_limit);
  window_.setVerticalSyncEnabled(win_cfg.vertical_sync);
  window_.setKeyRepeatEnabled(win_cfg.key_repeat_enabled);
  window_.setMouseCursorVisible(win_cfg.mouse_cursor_visible);
}

void App::run() {
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
