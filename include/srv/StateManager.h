#ifndef STATE_MANAGER_H
#define STATE_MANAGER_G

#include <stack>
#include <SFML/Graphics.hpp>


class StateManager {
 public:
    void handleInput();
    void update(sf::Time deltaTime);
 private:
    server tcp_server;
    void pop();
    void push(State);
    std::stack<Stack *>;
    GameContext;
}

#endif
