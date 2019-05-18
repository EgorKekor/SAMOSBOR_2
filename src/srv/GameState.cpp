//
// Created by kekor on 18.05.19.
//

#include "WaitState.h"
#include "GameState.h"
#include <memory>

using STATE_PTR = std::unique_ptr<State>;

GameState::GameState(StateManager &manager_, GameContext &context_) :  State(manager_, context_) {
    std::cout << "Режим игры\n";
}

bool GameState::handleStateInput() {
    
    return true;
}


bool GameState::updateState(sf::Time deltaTime) {

    return true;
}