#pragma once
#include <string>
#include <chrono>
#include <format>

#include "Colors.h"

namespace iamaprogrammer {
  class LogInfoComponents {
  public:
    static std::string getTime();
    static std::string getLogType(std::string type, std::string color);
  };
}