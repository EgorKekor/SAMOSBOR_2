#include "cli/AllStates.h"
#include "cli/GameState.h"

using std::make_unique;
using STATE_PTR = std::unique_ptr<State>;

GameState::GameState(StateManager *stack, GameContext &context_) : State(stack, context_) {
  lvl.LoadFromFile("../Graphics/map/map.tmx");
  MapObjects = lvl.GetAllObjects();

}
void GameState::handle_input(sf::Keyboard::Key key, bool isPressed) {
  if ((key == sf::Keyboard::Escape)&&(isPressed)) {
    STATE_PTR new_state = make_unique<MenuState>(stack, context);
    push_state(move(new_state));
  }

}
void GameState::handle_input(sf::Mouse::Button /*mouse*/, bool /*isPressed*/) {

}
void GameState::handle_input(char /*symbol*/) {

}
void GameState::update(sf::Time /*deltaTime*/) {
  for (auto npc = NPCs.rbegin(); npc != NPCs.rend(); npc++) {
    if ((*npc)->getHealth() > 0) {
      (*npc)->updateObject(/*deltaTime*/);
    }
  }

}
void GameState::draw() {
  context.mWindow->clear();
  lvl.Draw(*context.mWindow);
  context.mWindow->display();
}
