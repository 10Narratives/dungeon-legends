#include "config.hpp"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <system_error>
using engine::core::Config;
using engine::core::WindowConfig;

void engine::core::from_json(const json &j, WindowConfig &window_cfg) {
  j.at("vertical_sync").get_to(window_cfg.vertical_sync);
  j.at("key_repeat").get_to(window_cfg.key_repeat);
  j.at("title").get_to(window_cfg.title);
  j.at("framerate_limit").get_to(window_cfg.framerate_limit);
}

Config::Config(const std::filesystem::path &cfg_path) {
  if (!std::filesystem::is_regular_file(cfg_path)) {
    throw std::filesystem::filesystem_error(
        "configuration file does not exists by gotten path", cfg_path,
        std::make_error_code(std::errc::no_such_file_or_directory));
  }
  if (cfg_path.extension() != ".json") {
    throw std::filesystem::filesystem_error(
        "configuration file has unsupported extension", cfg_path,
        std::make_error_code(std::errc::not_supported));
  }

  std::ifstream cfg_file{cfg_path};
  if (!cfg_file.is_open()) {
    throw std::runtime_error{"cannot open configuration file"};
  }
  auto cfg_json = json::parse(cfg_file);
  cfg_file.close();

  cfg_json.at("window_config").get_to(window_cfg_);
}

const WindowConfig &Config::GetWindowConfig() const noexcept {
  return window_cfg_;
}