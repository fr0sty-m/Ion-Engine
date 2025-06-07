#pragma once

namespace Ion {

class Game;

class Core {
public:
  void run(Game *game);

  static Core &instance();

private:
  Core();
  ~Core();

  void initSDL();
  void createWindow();
  void pollEvents(bool &running);
  void calculateDeltaTime();

private:
  void *m_Window = nullptr;
  void *m_Context = nullptr;

  float m_LastTime = 0.0f;
  float m_DeltaTime = 0.0f;
};

} // namespace Ion
