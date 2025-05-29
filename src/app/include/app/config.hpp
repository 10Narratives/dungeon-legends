#pragma once

#include <cstdint>
#include <filesystem>
#include <spdlog/common.h>
#include <string>

#include <pugixml.hpp>
#include <spdlog/spdlog.h>

namespace app {
struct WindowConfig final {
  std::string title;
  int8_t bits_per_pixel;
  int8_t framerate_limit;
  bool vertical_sync;
  bool mouse_cursor_visible;
  bool key_repeat_enabled;
  std::filesystem::path icon_path;

  static WindowConfig readFrom(const pugi::xml_node& node);
};

struct LoggingConfig final {
  spdlog::level::level_enum level = spdlog::level::info;
  std::string pattern;

  static LoggingConfig readFrom(const pugi::xml_node& node);
};

class Config final {
 public:
  Config() = default;
  [[nodiscard]] const WindowConfig& getWindowConfig() const noexcept {return window_cfg_;}
  [[nodiscard]] const LoggingConfig& getLoggingConfig() const noexcept {return logging_cfg_;}

  [[nodiscard]] static Config readFrom(const std::filesystem::path& cfg_path);

 private:
  WindowConfig window_cfg_;
  LoggingConfig logging_cfg_;
};
}  // namespace app
