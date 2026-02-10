#include "./file.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#include <climits>
#endif

int FileIO::ensureDirectoryExists(const std::filesystem::path &dir) {
  if (std::filesystem::exists(dir)) {
    return 0;
  }
  try {
    std::filesystem::create_directories(dir);
    return 0;
  } catch (const std::exception &) {
    return 1;
  }
}

std::filesystem::path FileIO::getHomeDir() {
  const char *home = std::getenv("HOME");
  if (!home) {
    throw std::runtime_error("HOME environment variable is not set");
  }
  return std::filesystem::path(home);
}

std::filesystem::path FileIO::getExecutablePath() {
#if defined(__APPLE__)
  char buf[PATH_MAX];
  uint32_t bufsize = sizeof(buf);
  if (_NSGetExecutablePath(buf, &bufsize) != 0) {
    return {};
  }
  std::error_code ec;
  std::filesystem::path p = std::filesystem::canonical(buf, ec);
  return ec ? std::filesystem::path(buf) : p;
#else
  return {};
#endif
}

std::string FileIO::readFile(const std::filesystem::path &filepath) {
  std::ifstream inputFile(filepath);
  if (!inputFile) {
    throw std::runtime_error("Failed to open file: " + filepath.string());
  }
  return std::string(std::istreambuf_iterator<char>(inputFile),
                     std::istreambuf_iterator<char>());
}

void FileIO::writeFile(const std::filesystem::path &filepath,
  const std::string &content) {
std::ofstream out(filepath);
if (!out) {
throw std::runtime_error("Failed to open file for writing: " +
        filepath.string());
}
out << content;
if (!out) {
throw std::runtime_error("Failed to write file: " + filepath.string());
}
}

std::filesystem::path FileIO::getConfigDir() const { return m_configDir; }

void FileIO::setConfigDir(std::filesystem::path dir) {
  m_configDir = std::move(dir);
}
