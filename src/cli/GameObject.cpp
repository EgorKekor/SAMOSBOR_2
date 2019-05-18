#include "GameObject.h"

sf::Vector2f GameObject::getPossition() {
  return sf::Vector2f(x, y);
}
sf::FloatRect GameObject::getRect() {
  return sf::FloatRect();
}
int GameObject::getId() {
  return id;
}
std::string GameObject::getType() {
  return std::__cxx11::string(type);
}
int GameObject::getHealth() {
  return health;
}