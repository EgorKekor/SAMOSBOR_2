//
// Created by kekor on 18.05.19.
//

#include "srv/GameState.h"

using STATE_PTR = std::unique_ptr<State>;

GameState::GameState(StateManager &manager_, GameContext &context_) : State(manager_, context_) {
    Players.insert(std::make_pair(1, std::make_unique<Player>(context, sf::Vector2f(100, 100), 1)));
    Players.insert(std::make_pair(2, std::make_unique<Player>(context, sf::Vector2f(200, 200), 2)));
    context.GetMsgCreator().SendEntity(MULTICAST_ID, 1, Entityes::type::PLAYER, Entityes::Names::players::USUAL, sf::Vector2f(100, 100));
    context.GetMsgCreator().SendEntity(MULTICAST_ID, 2, Entityes::type::PLAYER, Entityes::Names::players::USUAL, sf::Vector2f(200, 200));
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
            Players[(*i).id()]->PressKey(size_t((*i).key(0)), true); // press key
        }
    }
}

void GameState::updateState(sf::Time /*deltaTime*/) {
}
