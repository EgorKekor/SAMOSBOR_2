#ifndef SERVER_NPC_H
#define SERVER_NPC_H

#include <iostream>
#include <memory>
#include "GameObject.h"

class NPC : public GameObject {
 public:
  using NPC_PTR = std::unique_ptr<NPC>;

  sf::FloatRect getRect() override;
  void drawObject() override;
  void updateObject(sf::Time deltaTime) override;
};

#endif //SERVER_NPC_H
