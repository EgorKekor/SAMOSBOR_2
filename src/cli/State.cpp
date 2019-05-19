#include "cli/State.h"
#include "cli/StateManager.h"

using std::make_unique;
using std::move;
using STATE_PTR = std::unique_ptr<State>;

State::State(StateManager *stack, GameContext &context_) : stack(stack), context(context_) {}

void State::push_state(STATE_PTR &&NewState) const {
  stack->push_state(move(NewState));
}

void State::pop_state() const {
  stack->pop_state();
}
