#include "core/config.h"
#include <filesystem>
#include <fstream>
#include <system_error>
using engine::core::Config;
using engine::core::WindowConfig;

Config::Config(const std::filesystem::path &config_path) {
  if (!std::filesystem::exists(config_path)) {
    throw std::filesystem::filesystem_error("configuration file not exists",
                                            std::error_code());
  }
  if (!std::filesystem::is_regular_file(config_path)) {
    throw std::filesystem::filesystem_error(
        "configuration file not a regular file", std::error_code());
  }
  std::ifstream config_file{config_path};
  if (!config_file.is_open()) {
    throw std::filesystem::filesystem_error("cannot open configuration file",
                                            std::error_code());
  }
  json config_date = json::parse(config_file);
  config_file.close();
  config_date.get_to(window_cfg_);
}

const WindowConfig &Config::GetWindowConfig() const { return window_cfg_; }