#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <SFML/Graphics.hpp>
#include <res/message.h>
#include <res/secure_queue.h>
#include <srv/server.h>
#include <srv/StateManager.h>
#include <queue>

class GameEngine {
 public:
  explicit GameEngine();
  int run();
 private:
  int handleInput();
  int update(sf::Time deltaTime);
  sf::RenderWindow Window;
  bool running;
  server Server;
  StateManager Manager;

};

#endif
