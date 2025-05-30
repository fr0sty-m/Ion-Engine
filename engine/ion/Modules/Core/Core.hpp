#pragma once

#include <string>

namespace Ion {

class Game;

class Core {
public:
  Core();
  ~Core();

  void setWindow(const std::string &title, int w, int h);

  void run(Game *game);

private:
  void pollEvents(bool &running);
  void calculateDeltaTime();

private:
  void *m_Window = nullptr;
  void *m_Context = nullptr;

  int m_Width, m_Height;
  std::string m_Title;

  float m_LastTime = 0.0f;
  float m_DeltaTime = 0.0f;
};

} // namespace Ion
