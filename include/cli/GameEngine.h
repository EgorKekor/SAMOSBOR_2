#ifndef SBOR_GAME_ENGINE_H_
#define SBOR_GAME_ENGINE_H_

#include "StateManager.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

class GameEngine {
 public:
  explicit GameEngine();
  bool run();
  bool input();
  bool update(sf::Time deltaTime);
  static void quit();
  static bool running();
 private:
  sf::RenderWindow mWindow;
  GameContext Context;
  StateManager manager;
  static bool running_;
};

#endif  //  INCLUDE_GAME_ENGINE_H_