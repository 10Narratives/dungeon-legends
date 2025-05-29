#include "app/app.hpp"
#include "app/config.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace app {
App::App(const app::Config& config) {
  initializeWindow(config.getWindowConfig());
  initializeLogger(config.getLoggingConfig());
}

void App::initializeWindow(const app::WindowConfig& win_cfg) {
  window_.create(sf::VideoMode::getDesktopMode(), win_cfg.title);
  window_.setFramerateLimit(win_cfg.framerate_limit);
  window_.setVerticalSyncEnabled(win_cfg.vertical_sync);
  window_.setKeyRepeatEnabled(win_cfg.key_repeat_enabled);
  window_.setMouseCursorVisible(win_cfg.mouse_cursor_visible);
}

void App::initializeLogger(const app::LoggingConfig& log_cfg) {
  auto console = spdlog::stdout_color_mt("console_logger");
  console->set_level(log_cfg.level);
  console->set_pattern(log_cfg.pattern);
  spdlog::set_default_logger(console);
}

void App::run() {
  spdlog::info("Start to run main loop");
  while (window_.isOpen()) {
    while (const auto& event = window_.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window_.close();
      }
    }

    window_.clear();
    window_.display();
  }
  spdlog::info("End of main loop");
}
}  // namespace app
