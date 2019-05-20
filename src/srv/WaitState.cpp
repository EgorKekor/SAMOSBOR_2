//
// Created by kekor on 10.05.19.
//

#include "srv/WaitState.h"
#include "srv/GameState.h"
#include <memory>

using STATE_PTR = std::unique_ptr<State>;

WaitState::WaitState(StateManager &manager_, GameContext &context_) :  State(manager_, context_) {
    std::cout << "Режим ожидания\n";
}


void WaitState::handleStateInput() {
    
}


void WaitState::updateState(sf::Time /*deltaTime*/) {
    if (context.GetServer().GetConnectNumb() == MAX_PLAYERS) {    // TO_DO(Stepan): Добавить метод, дающий число подключений
        SendStartMessage(context.GetServer());
        STATE_PTR gameState = std::make_unique<GameState>(manager, context);
        push_game_state(move(gameState));
    }
    std::cout << context.GetServer().GetConnectNumb() << "\n";
}


bool WaitState::SendStartMessage(server &srv) const {
    std::vector<message> &out = context.GetMessOutput();

    for (int i = 1; i <= MAX_PLAYERS; ++i) {
        context.GetMsgCreator().SendStart(i, MAX_PLAYERS);
    }

    for (auto &msg : out) {
        srv.push(msg);
    }
    out.clear();
    return true;
}

//bool WaitState::drawState() {
//
//}