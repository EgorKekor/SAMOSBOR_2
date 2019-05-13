#ifndef SERVER_WAITSTATE_H
#define SERVER_WAITSTATE_H

#include "State.h"
#include "GameEngine.h"

class WaitState : public State  {
 public:
  WaitState(StateManager *stack, GameContext &context_);
  void handle_input(sf::Keyboard::Key key, bool isPressed) override;
  void handle_input(sf::Mouse::Button mouse, bool isPressed) override;
  void update(sf::Time deltaTime) override;
  void draw() override;
 private:
  sf::Font font;
};


#endif //SERVER_WAITSTATE_H
