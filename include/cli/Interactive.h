#ifndef SERVER_INTERACTIVE_H
#define SERVER_INTERACTIVE_H

#include <iostream>
#include <memory>
#include "GameObject.h"

class Interactive: public GameObject {
 public:
  using INTERACTIVE_PTR = std::unique_ptr<Interactive>;

  void drawObject() override;
  void updateObject(sf::Time deltaTime) override;
};

#endif //SERVER_INTERACTIVE_H
