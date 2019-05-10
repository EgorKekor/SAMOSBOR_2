//
// Created by kekor on 10.05.19.
//

#include "WaitState.h"
#include <memory>

using STATE_PTR = std::unique_ptr<State>;

WaitState::WaitState(StateManager &manager_, GameContext &context_) :  State(manager_, context_) {
    std::cout << "Режим ожидания\n";
}


bool WaitState::handleStateInput() {
    
}


bool WaitState::updateState(sf::Time deltaTime) {
    if (context.GetServer().GetConnectNumb == 2) {    // TO_DO(Stepan): Добавить метод, дающий число подключений
        SendStartMessage(context.GetServer());
        STATE_PTR gameState = std::make_unique<GameState>(manager, context);
        manager.push_state(move(gameState));
    }
    return true;
}


bool WaitState::SendStartMessage(server &srv) const {
// TO_DO: Получить из context MessageCreator, сгенерировать messages
// и отправить всем игрокам (MessageCreator пушит месседжи в context.MessOutput<>)
// затем месседжи на отправку получить так: context.GetMessOutput()
}

//bool WaitState::drawState() {
//
//}