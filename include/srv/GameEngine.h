#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

class GameEngine {
 public:
    int run();
    int handleInput();
    int update(sf::TimedeltaTime);
    int quit();
 private:
    bool running;


};

#endif
