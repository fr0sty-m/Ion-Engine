#pragma once

// eger kullanicinin tanimladigi hicbir sey yoksa, sadece zorunlu modulleri
// yukler
#if !defined(REGISTER_CORE) && !defined(REGISTER_LOG) &&                       \
    !defined(REGISTER_INPUT) && !defined(REGISTER_IO) &&                       \
    !defined(REGISTER_ALL)

#define REGISTER_CORE
#define REGISTER_INPUT

#endif

// Eger REGISTER_ALL tanimliysa tum modulleri aktif eder
#ifdef REGISTER_ALL

#ifndef REGISTER_CORE
#define REGISTER_CORE
#endif

#ifndef REGISTER_LOG
#define REGISTER_LOG
#endif

#ifndef REGISTER_INPUT
#define REGISTER_INPUT
#endif

#ifdef REGISTER_IO
#define REGISTER_IO
#endif

// diger moduller
#endif

// modul bazli include
#ifdef REGISTER_CORE
#include "Modules/Config/Config.hpp"
#include "Modules/Config/WindowStyle.hpp"
#include "Modules/Core/Core.hpp"
#include "Modules/Core/Game.hpp"
#endif

#ifdef REGISTER_LOG
#include "Modules/Log/Log.hpp"
#endif

#ifdef REGISTER_INPUT
#include "Modules/Input/Input.hpp"
#include "Modules/Input/Key.hpp"
#endif

#ifdef REGISTER_IO
#include "Modules/IO/File.hpp"
#include "Modules/IO/JSON.hpp"
#endif

#define ION_MAIN(GameClass)                                                    \
  int main() {                                                                 \
    GameClass game;                                                            \
    Ion::Core::instance().run(&game);                                          \
    return 0;                                                                  \
  }

#define ION_WINDOW_CONFIG(TITLE, WIDTH, HEIGHT, STYLE)                         \
  namespace Ion {                                                              \
  static struct ConfigInitializer {                                            \
    ConfigInitializer() {                                                      \
      g_Config.title = TITLE;                                                  \
      g_Config.width = WIDTH;                                                  \
      g_Config.height = HEIGHT;                                                \
      g_Config.style = STYLE;                                                  \
    }                                                                          \
  } g_ConfigInitializerInstance;                                               \
  }

#define ION_WINDOW_CONFIG_S(TITLE, WIDTH, HEIGHT)                              \
  namespace Ion {                                                              \
  static struct ConfigInitializer {                                            \
    ConfigInitializer() {                                                      \
      g_Config.title = TITLE;                                                  \
      g_Config.width = WIDTH;                                                  \
      g_Config.height = HEIGHT;                                                \
    }                                                                          \
  } g_ConfigInitializerInstance;                                               \
  }
