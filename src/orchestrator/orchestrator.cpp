#include "./orchestrator.hpp"
#include "../process_launcher/process_launcher.hpp"
#include <boost/json.hpp>
#include <filesystem>
#include <iostream>
#include <stdexcept>

//-----------------------
//--- Private methods
//-----------------------

std::unordered_map<std::string, Workspace>
Orchestrator::parseWorkspaceJson(std::string_view fileContent) {
  const boost::json::value jsonValue = boost::json::parse(fileContent);
  const auto &root = jsonValue.as_object();
  const auto &workspaces = root.at("workspaces").as_object();
  std::unordered_map<std::string, Workspace> workspaceMap{};

  for (const auto &[key, value] : workspaces) {
    std::string workspaceName{key};
    Workspace workspace{workspaceName, parseCommandObject(value.as_object())};
    workspaceMap.insert({workspaceName, workspace});
  }
  return workspaceMap;
}

std::vector<Command>
Orchestrator::parseCommandObject(const boost::json::object &wsObject) {
  const auto &commandsArray = wsObject.at("commands").as_array();
  std::vector<Command> commands;

  for (const auto &commandValue : commandsArray) {
    const auto &cmdObj = commandValue.as_object();
    const std::string programName =
        std::string(cmdObj.at("program").as_string());

    std::vector<std::string> args;
    const auto &argsArray = cmdObj.at("args").as_array();

    for (const auto &argValue : argsArray) {
      args.push_back(std::string(argValue.as_string()));
    }

    bool detach = false;
    if (cmdObj.contains("detach") && cmdObj.at("detach").is_bool()) {
      detach = cmdObj.at("detach").as_bool();
    }
    std::string workspace {};
    if (cmdObj.contains("workspace") && cmdObj.at("workspace").is_string()) {
      workspace = cmdObj.at("workspace").as_string();
    }

    commands.push_back({programName, args, detach, workspace});
  }
  return commands;
}

void Orchestrator::executeWorkspace(const std::string &name) {
  if (!m_workspaceMap.contains(name)) {
    throw std::runtime_error("Workspace undefined: " + name);
  }

  std::cout << "Running workspace: " << name << '\n';
  Workspace &workspace = m_workspaceMap.at(name);

  for (const Command &command : workspace.commands) {
    ProcessLauncher p{};

    if (!command.workspace.empty()) {
      const std::vector<std::string> args{"workspace", command.workspace};
      p.run("aerospace", args);
    }

    if (command.detach) {
      p.runDetached(command.program, command.args);
    } else {
      p.run(command.program, command.args);
    }
    p.run("sleep", {"2"});
  }
};

//-----------------------
//--- Public methods
//-----------------------

std::unordered_map<std::string, Workspace>
Orchestrator::getWorkspaceMap() const {
  return m_workspaceMap;
}

void Orchestrator::ensureConfigExists() {
  const std::filesystem::path configDir = m_fileIO.getConfigDir();
  if (m_fileIO.ensureDirectoryExists(configDir) != 0) {
    throw std::runtime_error("Failed to create config directory: " +
                             configDir.string());
  }

  const std::filesystem::path configFilePath = configDir / "workspacer.json";
  if (std::filesystem::exists(configFilePath)) {
    return;
  }

  std::filesystem::path templatePath =
      std::filesystem::current_path() / "src" / "workspacer.config.json";
  std::string defaultContent = FileIO::readFile(templatePath);
  FileIO::writeFile(configFilePath, defaultContent);
}

void Orchestrator::loadConfigFile() {
  const std::filesystem::path configFilePath =
      m_fileIO.getConfigDir() / "workspacer.json";
  const std::string fileContent = FileIO::readFile(configFilePath);
  m_workspaceMap = parseWorkspaceJson(fileContent);
}

void Orchestrator::setWorkspaceMap(
    const std::unordered_map<std::string, Workspace> &workspace) {
  m_workspaceMap = workspace;
}
