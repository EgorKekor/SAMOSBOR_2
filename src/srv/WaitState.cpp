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
    if (context.GetServer().GetConnectNumb() == 2) {    // TO_DO(Stepan): Добавить метод, дающий число подключений
        SendStartMessage(context.GetServer());
        STATE_PTR gameState = std::make_unique<GameState>(manager, context);
        push_game_state(move(gameState));
    }
    if (context.GetServer().GetConnectNumb() == 1) {
        std::cout << "1 есть'\n";
    }
}


bool WaitState::SendStartMessage(server &srv) const {
    std::vector<message> &out = context.GetMessOutput();

    context.GetMsgCreator().SendStart();
    srv.push(out.back());
    out.pop_back();
    return true;
}

//bool WaitState::drawState() {
//
//}