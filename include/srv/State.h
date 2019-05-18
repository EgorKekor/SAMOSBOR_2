//
// Created by kekor on 10.05.19.
//

#ifndef SERVER_STATE_H
#define SERVER_STATE_H

#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <srv/GameContext.h>

class StateManager;

class State {
public:
    using STATE_PTR = std::unique_ptr<State>;

    explicit State(StateManager &manager_, GameContext &context_);
    virtual ~State() = default;

    virtual bool handleStateInput() = 0;
    virtual bool updateState(sf::Time deltaTime) = 0;
    //virtual bool drawState() = 0;
protected:
    void push_game_state(STATE_PTR &&NewState) const;
    void pop_game_state() const;

    StateManager &manager;
    GameContext &context;
private:

};


#endif //SERVER_STATE_H
