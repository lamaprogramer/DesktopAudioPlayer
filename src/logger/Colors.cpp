#include "../../include/logger/Colors.h"

namespace iamaprogrammer {
  std::string Colors::Black = "\x1b[1;30m";
  std::string Colors::Red = "\x1b[1;31m";
  std::string Colors::Green = "\x1b[1;32m";
  std::string Colors::Yellow = "\x1b[1;33m";
  std::string Colors::Blue = "\x1b[1;34m";
  std::string Colors::Magenta = "\x1b[1;35m";
  std::string Colors::Cyan = "\x1b[1;36m";
  std::string Colors::White = "\x1b[1;37m";

  std::string Colors::BrightBlack = "\x1b[1;90m";
  std::string Colors::BrightRed = "\x1b[1;91m";
  std::string Colors::BrightGreen = "\x1b[1;92m";
  std::string Colors::BrightYellow = "\x1b[1;93m";
  std::string Colors::BrightBlue = "\x1b[1;94m";
  std::string Colors::BrightMagenta = "\x1b[1;95m";
  std::string Colors::BrightCyan = "\x1b[1;96m";
  std::string Colors::BrightWhite = "\x1b[1;97m";

  std::string Colors::Terminate = "\x1b[39m";
}