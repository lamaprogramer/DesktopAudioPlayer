#include "../../include/logger/Logger.h"

namespace iamaprogrammer {
  void Logger::info(std::string message) {
    Logger::consoleLog(message);
  }

  void Logger::warn(std::string message) {
    Logger::consoleLog(message, "WARN", Colors::Yellow);
  }

  void Logger::error(std::string message, int level) {
    Logger::consoleLog(message, "ERROR", Colors::Red);
  }

  void Logger::consoleLog(std::string message, std::string type, std::string typeColor) {
    std::string fullLog = "";
    fullLog += LogInfoComponents::getTime();
    fullLog += LogInfoComponents::getLogType(type, typeColor);
    fullLog += " " + message;

    std::cout << fullLog << Colors::Terminate << std::endl;
  }

  void Logger::fileLog() {

  }
}