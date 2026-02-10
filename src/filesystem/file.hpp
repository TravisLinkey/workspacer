#pragma once

#include <filesystem>
#include <string>

/**
 * Generic file I/O helpers. No project-specific types or paths.
 * Reusable in other projects.
 */
class FileIO {
  std::filesystem::path m_configDir{};

public:
  FileIO() = default;

  int ensureDirectoryExists(const std::filesystem::path &dir);
  static std::filesystem::path getHomeDir();
  /** Returns absolute path to the running executable, or empty if unavailable. */
  static std::filesystem::path getExecutablePath();
  static std::string readFile(const std::filesystem::path &filepath);
  static void writeFile(const std::filesystem::path &filepath, const std::string &content);
  std::filesystem::path getConfigDir() const;
  void setConfigDir(std::filesystem::path dir);
};
