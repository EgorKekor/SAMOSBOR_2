//
// Created by kekor on 09.05.19.
//

#ifndef SERVER_MESSAGECREATOR_H
#define SERVER_MESSAGECREATOR_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <srv/server.h>
#include <res/Defines.h>

class MessageCreator{
public:
    MessageCreator(std::vector<message>& Outp);
    void SendBullet(size_t id, size_t bullet_id, size_t parent_id, sf::Vector2f target, size_t weapon_id) const;
    void SendDamage(size_t id, int damage, size_t object_type, size_t object_id) const;
    void SendEntity(size_t id, size_t object_id, size_t type, size_t name, sf::Vector2f position, int creator_id = -1) const;
    void SendMoving(size_t id, size_t object_id, size_t object_type, sf::Vector2f new_pos) const;
    void SendStart() const;

private:
    std::vector<message>& MessOutput;
};



#endif //SERVER_MESSAGECREATOR_H
