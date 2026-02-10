#include "io.hpp"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// ------------ INPUT

// ------------ OUTPUT
void io::printHelpMenu() {
  std::cout << "The following command line arguments are valid: \n";
  std::cout << "-h\t: Display the help menu\n";
}

void io::printWorkspaceName(std::string_view arg) {
  std::cout << "Running workspace: " << arg << '\n';
}

void io::printInvalidArgs() {
  std::cerr << "Invalid number of arguments\n";
  std::cerr << "-h or --help for more info.\n";
}

void io::printTooManyArgs() {
  std::cerr << "Invalid number of arguments\n";
  std::cerr << "Only one argument accepted\n";
}

void io::printProcessRunning(std::string_view p_name) {
  std::cout << "Running process: " << p_name << '\n';
}
