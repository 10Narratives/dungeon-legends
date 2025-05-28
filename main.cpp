#include <cstdlib>
#include <exception>
#include <iostream>

#include <app/app.hpp>

int main() {
    try {
        // TODO(): read configuration file
        // TODO(): prepare logger
        // TODO(): initialize application and call Run method
        auto app = app::App();
        app.Run();
    } catch (const std::exception& fatal_error) {
        std::cerr << fatal_error.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
