#include "process_launcher.hpp"
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

namespace {

/** Escape an argument for use inside double quotes in a shell command. */
std::string shellEscape(const std::string &arg) {
  std::string out;
  out.reserve(arg.size() + 2);
  for (char c : arg) {
    switch (c) {
      case '\\':
        out += "\\\\";
        break;
      case '"':
        out += "\\\"";
        break;
      case '\n':
        out += "\\n";
        break;
      case '$':
        out += "\\$";
        break;
      case '`':
        out += "\\`";
        break;
      default:
        out += c;
    }
  }
  return out;
}

} // namespace

std::string ProcessLauncher::encodeCommand(const std::string &program,
                                           const std::vector<std::string> &args) {
  std::ostringstream out;
  out << program;
  for (const auto &arg : args) {
    out << " \"" << shellEscape(arg) << '"';
  }
  return out.str();
}

int ProcessLauncher::run(const std::string &program,
                 const std::vector<std::string> &args) {

  auto cmd = encodeCommand(program, args);
  int result = std::system(cmd.c_str());
  return result;
}

int ProcessLauncher::runDetached(const std::string &program,
                                 const std::vector<std::string> &args) {
  auto cmd = encodeCommand(program, args);
  std::string detached = "( " + cmd + " & )";
  return std::system(detached.c_str());
}
