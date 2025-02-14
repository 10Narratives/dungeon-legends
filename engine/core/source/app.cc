#include "core/app.h"
#include "core/config.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <filesystem>
#include <optional>

using engine::core::App;

// TODO: Remove hardcode of config path
constexpr std::string cfg_path{"config.json"};

App::App() {
  Config cfg{cfg_path};
  initWindow(cfg.GetWindowConfig());
}

void App::initWindow(const WindowConfig &window_cfg) {
  window_.create(sf::VideoMode::getDesktopMode(), window_cfg.title);
  window_.setFramerateLimit(window_cfg.framerate_limit);
  window_.setVerticalSyncEnabled(window_cfg.vertical_sync);
  window_.setKeyRepeatEnabled(window_cfg.key_repeat);
}

void App::Run() {
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