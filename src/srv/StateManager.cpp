#include "StateManager.h"
#include "State.h"
#include "WaitState.h"

using STATE_PTR = std::unique_ptr<State>;



StateManager::StateManager(server &server_) : Context(server_) {
    STATE_PTR first_state = std::make_unique<WaitState>(this, Context);
    push_state(move(first_state));
}


void StateManager::push_state(STATE_PTR && new_state) {
    StatesStack.push_back(move(new_state));                 //  ? Проверить на удаление move
}


void StateManager::pop_state() {
    StatesBuf.push_back(move(StatesStack.back()));
    StatesStack.pop_back();
}

STATE_PTR& StateManager::get_state() {
    return StatesStack.back();
}



bool StateManager::handleInput() {
    /*TO_DO*/
    get_state()->handleStateInput();
    StatesBuf.clear();
}


bool StateManager::update(sf::Time deltaTime) {
    get_state()->updateState(deltaTime);
}

