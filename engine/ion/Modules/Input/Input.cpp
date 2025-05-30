#include "Input.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

namespace Ion {

std::unordered_map<Key, bool> Input::s_Current;
std::unordered_map<Key, bool> Input::s_Previous;
std::unordered_map<std::string, std::vector<Key>> Input::s_Bindings;

void Input::init() {
  s_Bindings["move_left"] = {Key::A, Key::Left};
  s_Bindings["move_right"] = {Key::D, Key::Right};
  s_Bindings["move_up"] = {Key::W, Key::Up};
  s_Bindings["move_down"] = {Key::S, Key::Down};
  s_Bindings["accept"] = {Key::Enter, Key::Space};
  s_Bindings["cancel"] = {Key::Escape, Key::Backspace};
  s_Bindings["debug_toggle"] = {Key::F1};
}

void Input::onEvent(int key, bool isKeyDown) {
  Key mappedKey = static_cast<Key>(key);
  s_Current[mappedKey] = isKeyDown;
}

void Input::update() { s_Previous = s_Current; }

bool Input::down(Key key) { return s_Current[key]; }

bool Input::pressed(Key key) { return s_Current[key] && !s_Previous[key]; }

bool Input::released(Key key) { return !s_Current[key] && s_Previous[key]; }

bool Input::action(const std::string &name) {
  auto it = s_Bindings.find(name);
  if (it == s_Bindings.end())
    return false;
  for (auto key : it->second) {
    if (down(key))
      return true;
  }
  return false;
}

bool Input::actionPressed(const std::string &name) {
  auto it = s_Bindings.find(name);
  if (it == s_Bindings.end())
    return false;
  for (auto key : it->second) {
    if (pressed(key))
      return true;
  }
  return false;
}

bool Input::actionReleased(const std::string &name) {
  auto it = s_Bindings.find(name);
  if (it == s_Bindings.end())
    return false;
  for (auto key : it->second) {
    if (released(key))
      return true;
  }
  return false;
}

const std::unordered_map<std::string, std::vector<Key>> &Input::getBindings() {
  return s_Bindings;
}

void Input::loadBinding(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open())
    return;

  nlohmann::json data;
  file >> data;

  for (auto &[action, keys] : data.items()) {
    std::vector<Key> keyList;
    for (const auto &k : keys) {
      std::string keyStr = k.get<std::string>();
      // Basitçe string -> Key çevir, örnek: "A" -> Key::A
      if (keyStr.length() == 1) {
        keyList.push_back(static_cast<Key>(tolower(keyStr[0])));
      }
      // Diğer özel tuşlar manuel eşlenebilir
      else if (keyStr == "Enter")
        keyList.push_back(Key::Enter);
      else if (keyStr == "Escape")
        keyList.push_back(Key::Escape);
      else if (keyStr == "Left")
        keyList.push_back(Key::Left);
      else if (keyStr == "Right")
        keyList.push_back(Key::Right);
      else if (keyStr == "Up")
        keyList.push_back(Key::Up);
      else if (keyStr == "Down")
        keyList.push_back(Key::Down);
    }
    s_Bindings[action] = keyList;
  }
}

} // namespace Ion
