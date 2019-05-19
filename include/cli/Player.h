#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include <iostream>
#include <memory>
#include "GameObject.h"

class Player: public GameObject {
 public:
  using PLAYER_PTR = std::unique_ptr<Player>;

  sf::FloatRect getRect() override;
  void drawObject() override;
  void updateObject(sf::Time deltaTime) override;
  void handle_actor_input(sf::Mouse::Button mouse, bool isPressed);
  void handle_actor_input(sf::Keyboard::Key key, bool isPressed);


  bool mainHero = false;
};

#endif //SERVER_PLAYER_H
