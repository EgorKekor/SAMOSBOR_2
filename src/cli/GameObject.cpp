#include "cli/GameObject.h"

GameObject::GameObject(GameContext &cnt, sf::Vector2f position, size_t id_) : context(cnt), id(id_), x(position.x), y(position.y){}

sf::Vector2f GameObject::getPossition() {
  return sf::Vector2f(x, y);
}
size_t GameObject::getId() {
  return id;
}
size_t GameObject::getType() {
  return type;
}
int GameObject::getHealth() {
  return health;
}