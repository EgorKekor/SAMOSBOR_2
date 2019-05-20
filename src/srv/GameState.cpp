//
// Created by kekor on 18.05.19.
//

#include "srv/GameState.h"

using STATE_PTR = std::unique_ptr<State>;

GameState::GameState(StateManager &manager_, GameContext &context_) : State(manager_, context_) {
    sf::Vector2f start(100, 100);
    for (int num = 0; num < MAX_PLAYERS; ++num) {
        Players.insert(std::make_pair(num + 1, std::make_unique<Player>(context, start, num + 1)));
        context.GetMsgCreator().SendEntity(num + 1, Entityes::type::PLAYER, Entityes::Names::players::USUAL, start);
        start.x += 100;
        start.y += 100;
    }

    PushMessages();
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
            Players[(*i).id()]->TakeShot((*i).mouse(0).mouse_x(), (*i).mouse(0).mouse_y(), (*i).mouse(0).is_pressed()); // take a shot to mouse_x, mouse_y coordinates
        }
        if ((*i).key_size() != 0) {
            Players[(*i).id()]->PressKey(size_t((*i).key(0).key()), bool((*i).key(0).is_pressed())); // press key
        }
    }
}

void GameState::updateState(sf::Time deltaTime) {
    for (auto player = Players.begin(); player != Players.end(); ++player) {
        player->second->updateObject(deltaTime);
    }
    PushMessages();
}



void GameState::PushMessages() {
    std::vector<message> &out = context.GetMessOutput();
    for (auto &msg : out) {
        context.GetServer().push(msg);
    }
    out.clear();
}