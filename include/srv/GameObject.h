#ifndef SERVER_GAMEOBJECT_H
#define SERVER_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <srv/GameContext.h>

class GameObject {
public:
    GameObject(GameContext &cnt, sf::Vector2f position, size_t id_);

    sf::Vector2f getPossition();
    int getHealth();
    size_t getId();
    size_t getType();

    virtual sf::FloatRect getRect() = 0;
    virtual void drawObject() = 0;
    virtual void updateObject(sf::Time deltaTime) = 0;
protected:
    GameContext &context;

    size_t id;
    size_t type;
    int health;
    float x;
    float y;
};

#endif //SERVER_GAMEOBJECT_H
