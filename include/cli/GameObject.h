#ifndef SERVER_GAMEOBJECT_H
#define SERVER_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <cli/GameContext.h>

class GameObject {
 public:
    void SetX(int x_) {x = x_;};
    void SetY(int y_) {y = y_;};
  GameObject(GameContext &cnt, int x, int y, size_t id_);

  sf::Vector2f getPossition();
  int getHealth();
  size_t getId();
  size_t getType();

  virtual sf::FloatRect getRect() = 0;
  virtual void drawObject() = 0;
  virtual void updateObject(sf::Time deltaTime) = 0;

 protected:
  GameContext &context;
  size_t id;
  size_t type;
  int health;
  int x;
  int y;
};

#endif //SERVER_GAMEOBJECT_H
