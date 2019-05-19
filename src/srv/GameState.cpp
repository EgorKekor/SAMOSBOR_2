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
        if (Players.find((*i).id()) == Players.end()) {
            std::cerr << "error: no players with id " << (*i).id() << std::endl;
            continue;
        }
        if ((*i).mouse_size() != 0) {
            Players[(*i).id()]->TakeShot((*i).mouse(0).mouse_x(), (*i).mouse(0).mouse_y()); // take a shot to mouse_x, mouse_y coordinates
        }
        if ((*i).key_size() != 0) {
            Players[(*i).id()]->PressKey((*i).key(0)); // press key
        }
    }
}

void GameState::updateState(sf::Time /*deltaTime*/) {
}
