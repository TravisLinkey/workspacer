#include "../filesystem/file.hpp"
#include "../workspace/workspace.hpp"
#include <boost/json.hpp>
#include <filesystem>
#include <unordered_map>

/**
 * Workspacer-specific business logic: config path, workspace parsing,
 * and orchestration. Uses FileIO for all actual file I/O.
 */
class Orchestrator {
  FileIO &m_fileIO;
  std::filesystem::path m_executablePath{};
  std::unordered_map<std::string, Workspace> m_workspaceMap;

private:
  std::unordered_map<std::string, Workspace> parseWorkspaceJson(std::string_view fileContent);
  std::vector<Command> parseCommandObject(const boost::json::object &wsObject);
  void ensureConfigExists();
  void loadConfigFile();

public:
  /** executablePath: optional; when set, template is resolved relative to it (avoids cwd-dependent paths when run via alias). */
  explicit Orchestrator(FileIO &fileIO, std::filesystem::path executablePath = {})
      : m_fileIO(fileIO), m_executablePath(std::move(executablePath)) {
    ensureConfigExists();
    loadConfigFile();
  }

  std::unordered_map<std::string, Workspace> getWorkspaceMap() const;
  void executeWorkspace(const std::string& name);
  void setWorkspaceMap(const std::unordered_map<std::string, Workspace> &workspace);
};
