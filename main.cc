#include <exception>
#include <spdlog/spdlog.h>

int main() {
  try {
    // Read env variables
    // Initialize application
    // Run application method
  } catch (const std::exception &fatal_error) {
    spdlog::error(fatal_error.what());
    return 1;
  }
  return 0;
}