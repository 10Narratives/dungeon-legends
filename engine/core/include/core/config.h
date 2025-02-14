#pragma once

#include <filesystem>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace engine::core {
/// WindowConfig implements configuration of window in game.
struct WindowConfig final {
  int width, height;
  int framerate_limit;
  bool vertical_sync;
  std::string title;
  bool key_repeat;
};

inline void from_json(const json &j, WindowConfig &window_cfg) {
  j.at("width").get_to(window_cfg.width);
  j.at("height").get_to(window_cfg.height);
  j.at("framerate_limit").get_to(window_cfg.framerate_limit);
  j.at("vertical_sync").get_to(window_cfg.vertical_sync);
  j.at("title").get_to(window_cfg.title);
  j.at("key_repeat").get_to(window_cfg.key_repeat);
}

/// Config implements configuration of all game.
class Config final {
public:
  /**
   * @brief Construct a new Config object reading application configuration from
   * file by `config path`.
   *
   * @param[in] config_path Path to configuration file.
   * @throws std::filesystem::filesystem_error In case if any errors are
   * occurred in configuration reading.
   */
  Config(const std::filesystem::path &config_path);

  /// WindowConfig retrieves configuration of window.
  [[nodiscard]] const WindowConfig &GetWindowConfig() const;

private:
  WindowConfig window_cfg_;
};
} // namespace engine::core