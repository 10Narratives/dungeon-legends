#include "core/app.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <filesystem>
#include <optional>

#include "core/config.h"
#include "spdlog/spdlog.h"

using engine::core::App;

// TODO: Remove hardcode of config path
const std::string cfg_path{"config/config.json"};

App::App() {
  spdlog::info("initializing application instance");
  spdlog::info("reading configuration file");
  Config cfg{cfg_path};
  spdlog::info("configuration file was readden successfully");
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