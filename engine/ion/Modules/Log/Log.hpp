#pragma once

#include <string>

namespace Ion {

enum class LogLevel { Info, Warning, Error };

class Log {
public:
  static void info(const std::string &message);
  static void warn(const std::string &message);
  static void err(const std::string &message);

private:
  static void print(LogLevel level, const std::string &message);
};

} // namespace Ion