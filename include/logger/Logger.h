#pragma once

#include <chrono>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include "LogInfoComponents.h"
#include "Colors.h"

namespace iamaprogrammer {
  class Logger {
  public:
    static void info(std::string message);
    static void warn(std::string message);
    static void error(std::string message, int level = 0);

  private:
    static void consoleLog(std::string message, std::string type = "INFO", std::string typeColor = Colors::Green);
    static void fileLog();
  };
}