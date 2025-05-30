#include "Core.hpp"
#include "Game.hpp"
#include "Input/Input.hpp"
#include "Log/Log.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <gl/GL.h>

#include <chrono>
#include <iostream>
#include <thread>

namespace Ion {

Core::Core() {
  // baslangic islemleri
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    Log::err("SDL Init Error");
    exit(1);
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_Window *window = SDL_CreateWindow(
      m_Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width,
      m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

  if (!window) {
    Log::err("SDL Window create error");
    Log::err(SDL_GetError());
    exit(1);
  }

  SDL_GLContext context = SDL_GL_CreateContext(window);
  if (!context) {
    Log::err("SDL_GL_CreateContext Error");
    Log::err(SDL_GetError());
    exit(1);
  }

  SDL_GL_SetSwapInterval(1);

  m_Window = window;
  m_Context = context;

  Input::init();
}

Core::~Core() {
  // temizlik islemleri
  SDL_GL_DeleteContext(static_cast<SDL_GLContext>(m_Context));
  SDL_DestroyWindow(static_cast<SDL_Window *>(m_Window));
  SDL_Quit();
}

void Core::run(Game *game) {
  game->start();

  bool running = true;
  m_LastTime = SDL_GetTicks() / 1000.0f;

  while (running) {
    pollEvents(running);
    calculateDeltaTime();

    Input::update();

    game->update(m_DeltaTime);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // TODO: Rendering Pipeline

    SDL_GL_SwapWindow(static_cast<SDL_Window *>(m_Window));

    SDL_Delay(16);
  }
}

void Core::pollEvents(bool &running) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      running = false;
    } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      int keycode = event.key.keysym.sym;
      bool down = event.type == SDL_KEYDOWN;
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

void Core::setWindow(const std::string &title, int w, int h) {
  m_Title = title;
  m_Width = w;
  m_Height = h;
}
} // namespace Ion
