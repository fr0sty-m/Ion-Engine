#include "Core.hpp"

#include "Config/Config.hpp"
#include "Game.hpp"
#include "Input/Input.hpp"
#include "Log/Log.hpp"
#include "SDL2/SDL_video.h"

#include <glad/glad.h>

#include <SDL2/SDL.h>

namespace Ion {

Core::Core() {
  initSDL();
  createWindow();

  Input::init();
}

Core::~Core() {
  SDL_GL_DeleteContext(static_cast<SDL_GLContext>(m_Context));
  SDL_DestroyWindow(static_cast<SDL_Window *>(m_Window));
  SDL_Quit();
}

Core &Core::instance() {
  static Core s_instance;
  return s_instance;
}

void Core::initSDL() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    Log::err("SDL init failed: " + std::string(SDL_GetError()));
    std::exit(-1);
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

void Core::createWindow() {
  SDL_Window *window = SDL_CreateWindow(
      g_Config.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      g_Config.width, g_Config.height, g_Config.style);

  if (!window) {
    Log::err("SDL window creation failed: " + std::string(SDL_GetError()));
    std::exit(-1);
  }

  SDL_GLContext context = SDL_GL_CreateContext(window);
  if (!context) {
    Log::err("OpenGL context creation failed: " + std::string(SDL_GetError()));
    std::exit(-1);
  }

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    Log::err("Failed to initialize GLAD");
    exit(-1);
  }

  SDL_GL_SetSwapInterval(1);

  m_Window = window;
  m_Context = context;
}

void Core::run(Game *game) {
  game->start();

  bool running = true;
  m_LastTime = SDL_GetTicks() / 1000.0f;

  while (running) {
    pollEvents(running);
    calculateDeltaTime();

    game->update(m_DeltaTime);

    Input::update();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // TODO: Rendering

    SDL_GL_SwapWindow(static_cast<SDL_Window *>(m_Window));
    SDL_Delay(1);
  }
}

void Core::pollEvents(bool &running) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
      int keycode = e.key.keysym.sym;
      bool down = e.type == SDL_KEYDOWN;
      Input::onEvent(keycode, down);

      if (keycode == SDLK_ESCAPE && down) {
        running = false;
      }
    }
  }
}

void Core::calculateDeltaTime() {
  float current = SDL_GetTicks() / 1000.0f;
  m_DeltaTime = current - m_LastTime;
  m_LastTime = current;
}

} // namespace Ion
