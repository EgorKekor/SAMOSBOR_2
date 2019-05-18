//
// Created by kekor on 10.05.19.
//

#ifndef SERVER_WAITSTATE_H
#define SERVER_WAITSTATE_H

#include "State.h"
#include "message.h"

#include <memory>
#include <string.h>
#include <iostream>


class WaitState : public State {
public:
    explicit WaitState(StateManager &manager_, GameContext &context_);
    bool handleStateInput() override;
    bool updateState(sf::Time deltaTime) override;
    //bool draw_game() override;
private:
    bool SendStartMessage(server &srv) const;
};


#endif //SERVER_WAITSTATE_H
