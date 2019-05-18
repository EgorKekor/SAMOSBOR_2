#ifndef SERVER_BULLET_H
#define SERVER_BULLET_H

#include <iostream>
#include <memory>
#include "GameObject.h"

class Bullet: public GameObject {
 public:
  using BULLET_PTR = std::unique_ptr<Bullet>;

  void drawObject() override;
  void updateObject() override;
};

#endif //SERVER_BULLET_H
