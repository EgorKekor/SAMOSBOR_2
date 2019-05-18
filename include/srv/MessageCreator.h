//
// Created by kekor on 09.05.19.
//

#ifndef SERVER_MESSAGECREATOR_H
#define SERVER_MESSAGECREATOR_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <server.h>
#include <Defines.h>

class MessageCreator{
    MessageCreator(std::vector<message>& Outp);
    bool SendBullet(size_t  bullet_id, size_t parent_id, sf::Vector2f target, size_t weapon_id);
    bool SendDamage(int damage, size_t object_type, size_t object_id);
    bool SendEntity(size_t id, size_t type, size_t name, sf::Vector2f position, int creator_id = -1);
    bool SendMoving(size_t object_id, size_t object_type, sf::Vector2f new_pos);

private:
    std::vector<message>& MessOutput;
};



#endif //SERVER_MESSAGECREATOR_H
