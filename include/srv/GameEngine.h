#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <SFML/Graphics.hpp>

class GameEngine {
 public:
    int run();
    int handleInput();
    int update(sf::Time deltaTime);
    int quit();
 private:
    bool running;


};

#endif
