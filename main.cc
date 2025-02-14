#include "engine/core/include/core/app.h"
#include <exception>
#include <iostream>

int main() {
  try {
    // Initialize application
    auto game = engine::core::App();
    // Call run method
    game.Run();
  } catch (const std::exception &fatal_error) {
    std::cout << fatal_error.what() << "\n";
    return 1;
  }
  return 0;
}