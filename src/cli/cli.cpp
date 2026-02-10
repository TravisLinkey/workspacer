#include "cli.hpp"
#include "../io/io.hpp"

int cli::handleArgs(int argc, char *argv[]) {

  if (argc == 1) {
    io::printInvalidArgs();
    return 1;
  }

  if (argc > 2) {
    io::printTooManyArgs();
    return 1;
  }

  std::string_view arg{argv[1]};

  if (arg == "-h" || arg == "--help") {
    io::printHelpMenu();
  } else {
    io::printWorkspaceName(arg);
  }

  return 0;
}
