#include "srv/Player.h"

Player::Player(GameContext &cnt, sf::Vector2f position, size_t id_) :
GameObject(cnt, position, id_), body(context.GetTextureManager().GetPlayerSize()),
mSprite(context.GetTextureManager().GetPlayerSprites()) {
}


sf::FloatRect Player::getRect() {

}

void Player::drawObject() {

}

void Player::updateObject() {

}

void Player::TakeShot(float x, float y) {
    return;
}

void Player::PressKey(size_t key, bool isPressed) {
    buttonState = isPressed;

    if (key == ) {
        actorParams_.Zpressed = true;
    }
    if (key == sf::Keyboard::F && !isPressed) {
        actorParams_.Fpressed = true;
    }
    if (key == sf::Keyboard::X && !isPressed) {
        actorParams_.Xpressed = true;
    }
    if (key == sf::Keyboard::C) {
        actorParams_.Cpressed = true;
    }

    if (key == sf::Keyboard::W) {
        actorParams_.mIsMovingUp = isPressed;
        actorParams_.spriteUp = true;
    }
    else if (key == sf::Keyboard::S) {
        actorParams_.mIsMovingDown = isPressed;
        actorParams_.spriteDown = true;
    }
    else if (key == sf::Keyboard::A) {
        actorParams_.mIsMovingLeft = isPressed;
        actorParams_.spriteLeft = true;
    }
    else if (key == sf::Keyboard::D) {
        actorParams_.mIsMovingRight = isPressed;
        actorParams_.spriteRight = true;
    } else if (key == sf::Keyboard::Num1) {
        actorParams_.current_weapon = (int)Weapon::Gun::Hand;
        actorParams_.spriteRight = true;
    } else if (key == sf::Keyboard::Num2) {
        actorParams_.current_weapon = (int)Weapon::Gun::Pistol;
    } else if (key == sf::Keyboard::Num3) {
        actorParams_.current_weapon = (int)Weapon::Gun::Automat;
    } else if (key == sf::Keyboard::Num4) {
        actorParams_.current_weapon = (int)Weapon::Gun::Usi;
    }

}
