#include <string>
#include <string_view>
#include <vector>

namespace io {
// Input

// Output
void printHelpMenu();
void printInvalidArgs();
void printProcessRunning(std::string_view p_name);
void printTooManyArgs();
void printWorkspaceName(std::string_view arg);
} // namespace io
