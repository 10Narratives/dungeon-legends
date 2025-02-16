#include "app.hpp"
#include "config.hpp"
#include <SFML/Window/VideoMode.hpp>
using engine::core::Application;

Application::Application() {
  // Read application config
  Config cfg{"config/config.json"};
  // Initialize window
  initWindow(cfg.GetWindowConfig());
}

void Application::initWindow(const engine::core::WindowConfig &cfg) {
  window_.create(sf::VideoMode::getDesktopMode(), cfg.title);
  window_.setKeyRepeatEnabled(cfg.key_repeat);
  window_.setVerticalSyncEnabled(cfg.vertical_sync);
  window_.setFramerateLimit(cfg.framerate_limit);
}

void Application::Run() {
  while (window_.isOpen()) {
    while (const std::optional event = window_.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window_.close();
      }
    }

    window_.clear();
    window_.display();
  }
}