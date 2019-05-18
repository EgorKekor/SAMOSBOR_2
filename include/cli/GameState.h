#ifndef SERVER_GAMESTATE_H
#define SERVER_GAMESTATE_H

#include "InteractiveObjects.h"
#include "Level.h"
#include "State.h"
#include "GameEngine.h"

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

};

#endif //SERVER_GAMESTATE_H
