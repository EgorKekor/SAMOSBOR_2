#ifndef SERVER_GAMESTATE_H
#define SERVER_GAMESTATE_H

#include "Level.h"
#include "State.h"
#include "GameEngine.h"
#include "AllGameObjects.h"


class GameState : public State  {
 public:
  GameState(StateManager *stack, GameContext &context_);
  void handle_input(sf::Keyboard::Key key, bool isPressed) override;
  void handle_input(sf::Mouse::Button mouse, bool isPressed) override;
  void handle_input(char symbol) override;
  void update(sf::Time deltaTime) override;
  void draw() override;

 private:
  Level lvl;
  std::vector<Object> MapObjects;

  std::vector<NPC::NPC_PTR> NPCs;
  std::vector<Player::PLAYER_PTR> Players;
  std::vector<Interactive::INTERACTIVE_PTR> InteractiveObjects;
  std::vector<Bullet::BULLET_PTR> Items;

};

#endif //SERVER_GAMESTATE_H
