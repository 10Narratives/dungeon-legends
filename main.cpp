#include "app/config.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>

#include <app/app.hpp>

std::filesystem::path getExecutableDir() {
    return std::filesystem::canonical(std::filesystem::path("/proc/self/exe")).parent_path();
}

int main() {
    try {
        auto exe_dir = getExecutableDir();
        auto cfg_path = exe_dir / "resources/configs/configuration.xml";

        auto cfg = app::Config::readFrom(cfg_path);

        auto app = app::App(cfg);
        app.run();
    } catch (const std::exception& fatal_error) {
        std::cerr << fatal_error.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
