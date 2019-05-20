//
// Created by kekor on 18.05.19.
//

#ifndef SERVER_GAMESTATE_H
#define SERVER_GAMESTATE_H

#include "srv/State.h"
#include "srv/WaitState.h"
#include "srv/Player.h"
#include "res/message.h"
#include <iostream>
#include <memory>

class GameState : public State {
public:
    using PLAYER_PTR = std::unique_ptr<Player>;
    explicit GameState(StateManager &manager_, GameContext &context_);
    void handleStateInput() override;
    void updateState(sf::Time deltaTime) override;
    //bool draw_game() override;
private:
    void PushMessages();
    std::map<size_t, PLAYER_PTR> Players;
};


#endif //SERVER_GAMESTATE_H
