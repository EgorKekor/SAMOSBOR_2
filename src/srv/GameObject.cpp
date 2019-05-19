#include "srv/GameObject.h"

GameObject::GameObject(GameContext &cnt, sf::Vector2f position, size_t id_) : x(position.x), y(position.y), id(id_),
context(cnt)
{};


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