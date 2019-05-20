#include "cli/AllStates.h"
#include "cli/GameState.h"

using std::make_unique;
using STATE_PTR = std::unique_ptr<State>;
using PLAYER_PTR = std::unique_ptr<Player>;

GameState::GameState(StateManager *stack, GameContext &context_) : State(stack, context_) {
  lvl.LoadFromFile("../Graphics/map/map.tmx");
  MapObjects = lvl.GetAllObjects();
  while (true) {
    if (context.Client.empty()) {
      continue;
    }
    std::vector<message> input = context.Client.GetInput();

    for (auto & msg : input) {
      if (msg.flag() == ServerMessages::MAKE_ENTITY) {
        PLAYER_PTR play = std::make_unique<Player>(context, sf::Vector2i(msg.entity(0).x(), msg.entity(0).y()), msg.entity(0).id());
        Players.push_back(move(play));
        break;
      }
    }
    break;
  }
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
void GameState::update(sf::Time deltaTime) {
  std::vector<message> input = context.Client.GetInput();
  for (auto msg = input.begin(); msg != input.end(); ++msg) {
    if ((*msg).move_size() != 0) {
      for (auto player = Players.begin(); player != Players.end(); ++player) {
        if ((*player)->getId() == (size_t)(*msg).move(0).object_id()) {
          (*player)->SetX((*msg).move(0).new_x());
          (*player)->SetY((*msg).move(0).new_y());
          break;
        }
      }
    } else if ((*msg).entity_size() != 0) {

    } else if ((*msg).bullet_size() != 0) {

    } else if ((*msg).damage_size() != 0) {

    }
  }

  for (auto npc = NPCs.rbegin(); npc != NPCs.rend(); npc++) {
    if ((*npc)->getHealth() > 0) {
      (*npc)->updateObject(deltaTime);
    }
  }

  for (auto player = Players.rbegin(); player != Players.rend(); player++) {
    if ((*player)->getHealth() > 0) {
      (*player)->updateObject(deltaTime);
    }
  }

  for (auto object = InteractiveObjects.rbegin(); object != InteractiveObjects.rend(); object++) {
    if ((*object)->getHealth() > 0) {
      (*object)->updateObject(deltaTime);
    }
  }

  for (auto bullet = Bullets.rbegin(); bullet != Bullets.rend(); bullet++) {
    if ((*bullet)->getHealth() > 0) {
      (*bullet)->updateObject(deltaTime);
    }
  }

}
void GameState::draw() {
  context.mWindow->clear();
  lvl.Draw(*context.mWindow);
  for (auto player = Players.rbegin(); player != Players.rend(); player++) {
    if ((*player)->getHealth() > 0) {
      (*player)->drawObject();
    }
  }
  context.mWindow->display();
}
