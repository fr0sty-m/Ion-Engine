#define REGISTER_ALL
#define INPUT_DEBUG
#include <ion/Ion.hpp>

class MyGame : public Ion::Game {
public:
  void start() override {}

  void update(float delta) override {}
};

ION_WINDOW_CONFIG_S("MyGame", 1280, 720);
ION_MAIN(MyGame);
