#include "StateManager.h"
#include "AllStates.h"
#include "State.h"

using std::make_unique;
using std::move;
using std::string;
using std::cin;
using STATE_PTR = std::unique_ptr<State>;

void StateManager::process_events(const sf::Event &event) {
  switch (event.type) {
    case sf::Event::MouseButtonPressed:get_state()->handle_input(event.mouseButton.button, true);
      break;
    case sf::Event::MouseButtonReleased:get_state()->handle_input(event.mouseButton.button, false);
      break;
    case sf::Event::KeyPressed:get_state()->handle_input(event.key.code, true);
      break;
    case sf::Event::KeyReleased:get_state()->handle_input(event.key.code, false);
      break;
    case sf::Event::TextEntered:get_state()->handle_input(static_cast<char>(event.text.unicode));
      break;
    default:break;
  }
  StatesBuf.clear();
}

StateManager::StateManager(GameContext &context) : Context(context) {
  STATE_PTR first_state = make_unique<MenuState>(this, Context);
  push_state(move(first_state));
}

void StateManager::push_state(STATE_PTR &&new_state) {
  StatesStack.push_back(move(new_state));
}

void StateManager::pop_state() {
  StatesBuf.push_back(move(StatesStack.back()));
  StatesStack.pop_back();
}

STATE_PTR &StateManager::get_state() {
  return StatesStack.back();
}

void StateManager::update(sf::Time deltaTime) {
  get_state()->update(deltaTime);
}

void StateManager::draw() {
  get_state()->draw();
}

size_t StateManager::get_states_size() {
  return (StatesStack.size());
}


