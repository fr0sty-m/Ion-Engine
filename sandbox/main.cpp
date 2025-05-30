#include "ion/Modules/Input/Input.hpp"
#include "ion/Modules/Input/Key.hpp"
#include "ion/Modules/Log/Log.hpp"
#define REGISTER_ALL
#include <ion/Ion.hpp>

#include <iostream>

class MyGame : public Ion::Game {
public:
  void start() override {}

  void update(float delta) override {
    //
    if (Ion::Input::pressed(Ion::Key::Space)) {
      Ion::Log::info("Space");
    }
  }
};

ION_MAIN(MyGame);
