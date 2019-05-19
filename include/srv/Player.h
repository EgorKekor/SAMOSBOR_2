#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include "srv/GameObject.h"

class Player : public GameObject {
public:
    Player(GameContext &cnt, sf::Vector2f position, size_t id_);

    PlayerSize const &body;             //  Тело отрисовки


    sf::Clock clock;
    sf::Time timeSinceLastChangeViev;
    sf::Time timeViewChange;
    sf::Clock fireClock;
    sf::Time fireReaction;
    sf::Time fireReactionTimer;

    sf::Vector2f mpuseTouch;
    sf::Vector2f mpuseUnTouch;
    size_t current_weapon;
    size_t speed;
    float dx;
    float dy;

    bool buttonState;
    bool mouseState;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;

    // =================    FOR CLIENT
    /*std::vector<std::vector<std::vector<sf::Sprite>>> const &mSprite;
    bool spriteUp;
    bool spriteDown;
    bool spriteLeft;
    bool spriteRight;*/
    // =================


    sf::FloatRect getRect() override;
    void drawObject() override;
    void updateObject(sf::Time deltaTime) override;
    void TakeShot(float x, float y, bool isPressed);
    void PressKey(size_t key, bool isPressed);
protected:

};

#endif //SERVER_PLAYER_H
