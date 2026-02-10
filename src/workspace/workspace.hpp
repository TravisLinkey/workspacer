#include <ostream>
#include <string>
#include <vector>

struct Command {
  std::string program;
  std::vector<std::string> args;
  bool detach{false};
  std::string workspace{};

  friend std::ostream &operator<<(std::ostream &out, const Command &command) {
    out << command.program;

    for (const std::string &arg : command.args) {
      out << ' ' << arg;
    }
    out << '\n';

    return out;
  }
};

struct Workspace {
  std::string name;
  std::vector<Command> commands;

  friend std::ostream &operator<<(std::ostream &out,
                                  const Workspace &workspace) {
    out << workspace.name << ':' << '\n';

    for (const Command &command : workspace.commands) {
      out << command << '\n';
    }

    out << '\n';

    return out;
  }
};
