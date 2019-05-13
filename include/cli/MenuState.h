#ifndef SERVER_MENUSTATE_H
#define SERVER_MENUSTATE_H

#include "State.h"
#include "GameEngine.h"

class StateManager;

class MenuState : public State  {
 public:
  MenuState(StateManager *stack, GameContext &context_);
  void handle_input(sf::Keyboard::Key key, bool isPressed) override;
  void handle_input(sf::Mouse::Button mouse, bool isPressed) override;
  //void handle_input();
  void update(sf::Time deltaTime) override;
  void draw() override;
 private:
  int menuNum = 0;
  sf::Texture buttonTexture, backgroundTexture;
  sf::Sprite exitSprite, gameSprite, backgroundSprite;
  sf::Font font;
};

#endif //SERVER_MENUSTATE_H
