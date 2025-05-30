#pragma once

namespace Ion {

class Game {
public:
  virtual ~Game() = default;

  virtual void start() = 0;
  virtual void update(float delta) = 0;
};

} // namespace Ion