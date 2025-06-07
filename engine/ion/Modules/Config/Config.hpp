#pragma once

#include "WindowStyle.hpp"

#include <cstdint>
#include <string>

namespace Ion {

struct Config {
  std::string title = "Ion Game";
  int width = 1920;
  int height = 1080;
  uint32_t style = WindowStyle::RESIZABLE | WindowStyle::OPENGL |
                   WindowStyle::SHOWN | WindowStyle::MAXIMIZED;
};

extern Config g_Config;

} // namespace Ion
