#include "../io/io.hpp"

struct ProcessLauncher {
  int exit_code{0};

  std::string encodeCommand(const std::string &program,
                            const std::vector<std::string> &args);

  int run(const std::string &program, const std::vector<std::string> &args);

  /** Run in background and detach so the process survives when workspacer exits. */
  int runDetached(const std::string &program,
                  const std::vector<std::string> &args);
};
