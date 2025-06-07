#define REGISTER_ALL
#include <ion/Ion.hpp>

class MyGame : public Ion::Game {
public:
  void start() override {}

  void update(float delta) override {}
};

ION_WINDOW_CONFIG("MyGame", 1280, 720,
                  Ion::WindowStyle::OPENGL | Ion::WindowStyle::RESIZABLE |
                      Ion::WindowStyle::SHOWN);
ION_MAIN(MyGame);
