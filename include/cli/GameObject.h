#ifndef SERVER_GAMEOBJECT_H
#define SERVER_GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject {
 public:
  virtual sf::Vector2f getPossition() = 0;
  virtual sf::FloatRect getRect() = 0;
  virtual int getId() = 0;
  virtual std::string getType() = 0;
  virtual int getHealth() = 0;
  virtual void drawObject() = 0;
  virtual void updateObject() = 0;

 protected:
  int id;
  std::string type;
  int health;
  int width;
  int height;
  float x;
  float y;
};

#endif //SERVER_GAMEOBJECT_H
