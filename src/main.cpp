#include "./cli/cli.hpp"
#include "./filesystem/file.hpp"
#include "./orchestrator/orchestrator.hpp"
#include "./process_launcher/process_launcher.hpp"
#include <filesystem>
#include <iostream>

int main(int argc, char *argv[]) {
  cli::handleArgs(argc, argv);

  try {
    FileIO fileIO{};
    std::filesystem::path configDir = FileIO::getHomeDir() / ".config" / "workspacer";
    fileIO.setConfigDir(configDir.is_relative() ? std::filesystem::absolute(configDir) : configDir);

    std::filesystem::path exePath = FileIO::getExecutablePath();
    Orchestrator orchestrator{fileIO, std::move(exePath)};
    orchestrator.executeWorkspace(argv[1]);

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }

  return 0;
}
