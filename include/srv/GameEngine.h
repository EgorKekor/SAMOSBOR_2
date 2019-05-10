#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <SFML/Graphics.hpp>
#include <../res/message.h>
#include <../res/secure_queue.h>
#include <server.h>
#include <StateManager.h>
#include <queue>

class GameEngine {
 public:
    explicit GameEngine();
    int run();
 private:
    int handleInput();
    int update(sf::Time deltaTime);
    bool running;
    sf::RenderWindow Window;
    StateManager Manager;
    server Server;

};

#endif
