#include <exception>
#include <iostream>

int main() {
  try {
    // Initialize application
    // Call run method
  } catch (const std::exception &fatal_error) {
    std::cout << fatal_error.what() << "\n";
    return 1;
  }
  return 0;
}