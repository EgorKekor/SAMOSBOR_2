#include "srv/Player.h"

Player::Player(GameContext &cnt, sf::Vector2f position, size_t id_) :
GameObject(cnt, position, id_), body(context.GetTextureManager().GetPlayerSize())
//mSprite(context.GetTextureManager().GetPlayerSprites())
{
    health = 1000;
    speed = 100;
    buttonState = false;
    mouseState = false;
    mIsMovingUp = false;
    mIsMovingDown = false;
    mIsMovingLeft = false;
    mIsMovingRight = false;
}


void Player::PressKey(size_t key, bool isPressed) {
    buttonState = isPressed;

    if (key == ClientMessages::key::W) {
        mIsMovingUp = isPressed;
    }
    else if (key == ClientMessages::key::S) {
        mIsMovingDown = isPressed;
    }
    else if (key == ClientMessages::key::A) {
        mIsMovingLeft = isPressed;
    }
    else if (key == ClientMessages::key::D) {
        mIsMovingRight = isPressed;
    } else if (key == ClientMessages::key::NUM1) {
        current_weapon = Weapon::Gun::HAND;
    } else if (key == ClientMessages::key::NUM2) {
        current_weapon = Weapon::Gun::PISTOL;
    } else if (key == ClientMessages::key::NUM3) {
        current_weapon = Weapon::Gun::AUTOMAT;
    }
}


void Player::TakeShot(float x, float y, bool isPressed) {
    mouseState = isPressed;
    if (mouseState) {
        mpuseTouch.x = x;
        mpuseTouch.y = y;
    } else {
        museUnTouch.x = x;
        museUnTouch.y = y;
    }

}


void Player::drawObject() {

}

void Player::updateObject(sf::Time deltaTime) {
    dx = dy = 0;

    if (mIsMovingUp) {
        dx = 0;
        dy = -(speed);
    }

    if (mIsMovingDown) {
        dx = 0;
        dy = speed;
    }

    if (mIsMovingLeft) {
        dx = -(speed);
        dy = 0;
    }

    if (mIsMovingRight) {
        dx = speed;
        dy = 0;
    }

    x = x + (dx * deltaTime.asSeconds());
    y = y + (dy * deltaTime.asSeconds());

    if (dx != 0 || dy != 0) {
        context.GetMsgCreator().SendMoving(id, type, sf::Vector2f(x, y));
    }
}



sf::FloatRect Player::getRect() {
    return sf::FloatRect(x - body.width/2, y - body.height/2, body.width, body.height);
}