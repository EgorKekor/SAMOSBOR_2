#ifndef SERVER_WAITSTATE_H
#define SERVER_WAITSTATE_H

#include "State.h"
#include "GameEngine.h"
#include <ctype.h>

class WaitState : public State  {
 public:
  WaitState(StateManager *stack, GameContext &context_);
  void handle_input(sf::Keyboard::Key key, bool isPressed) override;
  void handle_input(sf::Mouse::Button mouse, bool isPressed) override;
  void handle_input(char symbol) override;
  void update(sf::Time deltaTime) override;
  void draw() override;

  bool is_ipv4_address();
 private:
  sf::Font font;
  sf::Text text, helpText, errorText;

  std::string address;
  bool connectionEstablished;
  bool ipError;
};


#endif //SERVER_WAITSTATE_H
