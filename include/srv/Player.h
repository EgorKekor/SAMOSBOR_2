#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
public:
    sf::FloatRect getRect() override;
    void drawObject() override;
    void updateObject() override;
    void TakeShot(float, float);
    void PressKey(int);
protected:

};

#endif //SERVER_PLAYER_H
