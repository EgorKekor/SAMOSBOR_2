#ifndef STATE_MANAGER_H
#define STATE_MANAGER_G
#include <stack>

class StateManager {
 public:
    void update();
    void handleInput(sf::TimedeltaTime);
 private:
    server tcp_server;
    void pop();
    void push(State);
    std::stack<Stack *>
    GameContext;
}

#endif
