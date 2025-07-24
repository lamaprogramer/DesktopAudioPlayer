#include "../../include/logger/LogInfoComponents.h"

namespace iamaprogrammer {
  std::string LogInfoComponents::getTime() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    now = std::chrono::floor<std::chrono::seconds>(now); // Round down to the nearest second
    return std::format("[{:%X}]", now);
  }

  std::string LogInfoComponents::getLogType(std::string type, std::string color) {
    return color + "[" + type + "]" + Colors::Terminate;
  }
}