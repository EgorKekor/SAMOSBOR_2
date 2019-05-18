#ifndef STATE_MANAGER_H
#define STATE_MANAGER_G

#include <stack>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <GameContext.h>
#include <State.h>
#include <server.h>


class StateManager {
    using STATE_PTR = std::unique_ptr<State>;
public:
    explicit StateManager(sf::RenderWindow &Window_, server &server_);

    bool handleInput();
    bool update(sf::Time deltaTime);
    //bool draw();

    void push_state(STATE_PTR &&new_state);
    void pop_state();
    size_t get_size() const {return StatesStack.size();};

private:
    STATE_PTR &get_state();

    std::vector<STATE_PTR> StatesStack;
    std::vector<STATE_PTR> StatesBuf;
    GameContext Context;
};



#endif
