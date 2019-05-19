//
// Created by kekor on 18.05.19.
//

#include "srv/WaitState.h"
#include "srv/GameState.h"
#include <memory>

using STATE_PTR = std::unique_ptr<State>;

GameState::GameState(StateManager &manager_, GameContext &context_) : State(manager_, context_) {
  std::cout << "Режим игры\n";
}

void GameState::handleStateInput() {
}

void GameState::updateState(sf::Time /*deltaTime*/) {
}