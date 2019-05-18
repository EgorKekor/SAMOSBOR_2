//
// Created by kekor on 10.05.19.
//

#include "srv/State.h"
#include "srv/StateManager.h"

using std::make_unique;
using std::move;
using STATE_PTR = std::unique_ptr<State>;


State::State(StateManager &manager_, GameContext &context_) : manager(manager_), context(context_) {}


void State::push_game_state(STATE_PTR &&NewState) const {
    manager.push_state(move(NewState));
}


void State::pop_game_state() const {
    manager.pop_state();
}



