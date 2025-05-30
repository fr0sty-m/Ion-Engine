#include "Log.hpp"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Ion {

void Log::info(const std::string &message) { print(LogLevel::Info, message); }

void Log::warn(const std::string &message) {
  print(LogLevel::Warning, message);
}

void Log::err(const std::string &message) { print(LogLevel::Error, message); }

void Log::print(LogLevel level, const std::string &message) {
  // Renkler (Linux ANSI veya Windows API)
#ifdef _WIN32
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
  WORD saved_attributes;

  GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
  saved_attributes = consoleInfo.wAttributes;

  switch (level) {
  case LogLevel::Info:
    SetConsoleTextAttribute(hConsole, 7);
    break;
  case LogLevel::Warning:
    SetConsoleTextAttribute(hConsole, 6);
    break;
  case LogLevel::Error:
    SetConsoleTextAttribute(hConsole, 4);
    break;
  }
#else
  switch (level) {
  case LogLevel::Info:
    std::cout << "\033[0m";
    break; // Default
  case LogLevel::Warning:
    std::cout << "\033[33m";
    break; // Yellow
  case LogLevel::Error:
    std::cout << "\033[31m";
    break; // Red
  }
#endif

  // Mesaj
  switch (level) {
  case LogLevel::Info:
    std::cout << "[INFO] ";
    break;
  case LogLevel::Warning:
    std::cout << "[WARN] ";
    break;
  case LogLevel::Error:
    std::cout << "[ERROR] ";
    break;
  }

  std::cout << message << std::endl;

#ifdef _WIN32
  SetConsoleTextAttribute(hConsole, saved_attributes);
#else
  std::cout << "\033[0m"; // Reset
#endif
}

} // namespace Ion