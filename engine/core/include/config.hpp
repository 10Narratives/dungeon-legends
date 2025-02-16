#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace engine::core {

/// WindowConfig contains configuration of window.
struct WindowConfig final {
public:
  bool vertical_sync;
  bool key_repeat;
  std::string title;
  int framerate_limit;
};

void from_json(const json &j, WindowConfig &window_cfg);

/// Config contain configuration of all application.
class Config final {
public:
  Config() = default;

  /// Constructs new Config instance by gotten `cfg_path`.
  /**
    @param[in] cfg_path Path to configuration file.
    @throws std::filesystem::filesystem_error If an error occurs while reading
    the configuration file.
    @throws std::runtime_error If could not open the configuration file.
  */
  explicit Config(const std::filesystem::path &cfg_path);

  /// GetWindowConfig retrieves configuration of `sf::RenderWindow`.
  [[nodiscard]] const WindowConfig &GetWindowConfig() const noexcept;

private:
  WindowConfig window_cfg_;
};

} // namespace engine::core