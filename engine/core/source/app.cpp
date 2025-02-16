#include "app.hpp"
using engine::core::Application;

Application::Application() {
  // Read application config
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