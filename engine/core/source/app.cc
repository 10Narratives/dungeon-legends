#include "core/app.h"
#include "core/config.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <filesystem>
#include <iostream>
#include <optional>
using engine::core::App;

App::App() {
  // TODO: Remove hardcode of config path
  std::filesystem::path config_path{"config.json"};
  Config cfg{config_path};
  const auto &window_cfg = cfg.GetWindowConfig();

  std::cout << window_cfg.width << window_cfg.height
            << window_cfg.framerate_limit << window_cfg.title
            << window_cfg.key_repeat << window_cfg.vertical_sync << std::endl;

  window_.create(sf::VideoMode::getDesktopMode(), "Dungeon Legends");
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