#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include <iostream>
#include <memory>
#include "GameObject.h"

class Player: public GameObject {
 public:
  using PLAYER_PTR = std::unique_ptr<Player>;

  void drawObject() override;
  void updateObject() override;
};

#endif //SERVER_PLAYER_H
