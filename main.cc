#include <exception>
#include <iostream>

int main() {
  try {

  } catch (const std::exception &fatal_err) {
    std::cout << fatal_err.what() << std::endl;
    return -1;
  }
  return 0;
}