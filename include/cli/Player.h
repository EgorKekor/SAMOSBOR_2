#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include <iostream>
#include <memory>
#include "GameObject.h"

class Player: public GameObject {
 public:
  using PLAYER_PTR = std::unique_ptr<Player>;
  Player(GameContext &context_, float x, float y, size_t id_);


  sf::FloatRect getRect() override;
  void drawObject() override;
  void updateObject(sf::Time deltaTime) override;
  void handle_actor_input(sf::Mouse::Button mouse, bool isPressed);
  void handle_actor_input(sf::Keyboard::Key key, bool isPressed);
  void setPlayerView(float x, float y);

  bool isMovingUp;
  bool isMovingDown;
  bool isMovingLeft;
  bool isMovingRight;


  sf::Clock clock;
  sf::Time timeSinceLastChangeView;
  sf::Time timeViewChange;
  sf::Clock fireClock;
  sf::Time fireReaction;
  sf::Time fireReactionTimer;

  sf::CircleShape circle{ 100.f };

  //sf::Sprite playerSprite;
  sf::CircleShape shape;
  bool mainHero = false;
};

#endif //SERVER_PLAYER_H
