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
  for (auto player = Players.rbegin(); player != Players.rend(); player++) {
    if ((*player)->mainHero) {
      (*player)->handle_actor_input(key, isPressed);
    }
  }
}
void GameState::handle_input(sf::Mouse::Button mouse, bool isPressed) {
  for (auto player = Players.rbegin(); player != Players.rend(); player++) {
    if ((*player)->mainHero) {
      (*player)->handle_actor_input(mouse, isPressed);
    }
  }
}
void GameState::handle_input(char /*symbol*/) {

}
void GameState::update(sf::Time /*deltaTime*/) {
  for (auto npc = NPCs.rbegin(); npc != NPCs.rend(); npc++) {
    if ((*npc)->getHealth() > 0) {
      (*npc)->updateObject(/*deltaTime*/);
    }
  }

  for (auto player = Players.rbegin(); player != Players.rend(); player++) {
    if ((*player)->getHealth() > 0) {
      (*player)->updateObject(/*deltaTime*/);
    }
  }

  for (auto object = InteractiveObjects.rbegin(); object != InteractiveObjects.rend(); object++) {
    if ((*object)->getHealth() > 0) {
      (*object)->updateObject(/*deltaTime*/);
    }
  }

  for (auto bullet = Bullets.rbegin(); bullet != Bullets.rend(); bullet++) {
    if ((*bullet)->getHealth() > 0) {
      (*bullet)->updateObject(/*deltaTime*/);
    }
  }

}
void GameState::draw() {
  context.mWindow->clear();
  lvl.Draw(*context.mWindow);
  context.mWindow->display();
}
