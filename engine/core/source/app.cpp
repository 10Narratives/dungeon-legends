#include "app.hpp"
#include "config.hpp"
using engine::core::Application;

Application::Application() {
  // Read application config
  Config cfg{"config/config.json"};
  // Initialize window
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