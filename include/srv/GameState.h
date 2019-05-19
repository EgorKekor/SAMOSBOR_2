//
// Created by kekor on 18.05.19.
//

#ifndef SERVER_GAMESTATE_H
#define SERVER_GAMESTATE_H

#include "State.h"
#include "srv/WaitState.h"
#include "res/message.h"
#include <iostream>
#include <memory>

class GameState : public State {
public:
    explicit GameState(StateManager &manager_, GameContext &context_);
    void handleStateInput() override;
    void updateState(sf::Time deltaTime) override;
    //bool draw_game() override;
private:
};


#endif //SERVER_GAMESTATE_H
