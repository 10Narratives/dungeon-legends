#include "app/config.hpp"
#include "spdlog/common.h"

#include <cstdint>
#include <pugixml.hpp>
#include <stdexcept>

namespace app {
WindowConfig WindowConfig::readFrom(const pugi::xml_node &window_node) {
  if (!window_node) {
    throw std::runtime_error{"XML file is missing the <window> element."};
  }
  WindowConfig window_cfg;
  window_cfg.title = window_node.child("title").text().as_string();
  window_cfg.bits_per_pixel = static_cast<int8_t>(window_node.child("bitsPerPixel").text().as_int());
  window_cfg.framerate_limit = static_cast<int8_t>(window_node.child("frameRateLimit").text().as_int());
  window_cfg.vertical_sync = window_node.child("verticalSync").text().as_bool();
  window_cfg.mouse_cursor_visible = window_node.child("mouseCursorVisible").text().as_bool();
  window_cfg.key_repeat_enabled = window_node.child("keyRepeatEnabled").text().as_bool();
  window_cfg.icon_path = std::filesystem::path(window_node.child("icon").text().as_string());
  return window_cfg;
}

LoggingConfig LoggingConfig::readFrom(const pugi::xml_node &logging_node) {
  if (!logging_node) {
    throw std::runtime_error{"XML file is missing the <logging> element."};
  }

  LoggingConfig config;
  const auto *level = logging_node.child("level").text().as_string();
  auto ll = spdlog::level::from_str(level);
  config.level = ll;
  config.pattern = logging_node.child("pattern").text().as_string();
  return config;
}

Config Config::readFrom(const std::filesystem::path &cfg_path) {
  if (!std::filesystem::exists(cfg_path)) {
    throw std::runtime_error{"Configuration file not found: " + cfg_path.string()};
  }

  Config config;

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(cfg_path.string().c_str());
  if (!result) {
    throw std::runtime_error{"Failed to parse XML file: " + cfg_path.string() + ". Error: " + result.description()};
  }

  pugi::xml_node root = doc.child("configuration");
  if (!root) {
    throw std::runtime_error("XML file is missing the <configuration> root element.");
  }

  config.window_cfg_ = WindowConfig::readFrom(root.child("window"));
  config.logging_cfg_ = LoggingConfig::readFrom(root.child("logging"));

  return config;
}

}  // namespace app
