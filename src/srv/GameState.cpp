//
// Created by kekor on 18.05.19.
//

#include "srv/GameState.h"

using STATE_PTR = std::unique_ptr<State>;

GameState::GameState(StateManager &manager_, GameContext &context_) : State(manager_, context_) {
  std::cout << "Режим игры\n";
}

void GameState::handleStateInput() {
    std::vector<message> messages = context.GetServer().get_msg_vector();
    for (auto i = messages.begin(); i != messages.end(); i++) {
        //обработка клиентских сообщений

    }
}

void GameState::updateState(sf::Time /*deltaTime*/) {
}
