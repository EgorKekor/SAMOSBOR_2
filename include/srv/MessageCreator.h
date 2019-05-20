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
    void SendBullet(int bullet_id, int parent_id, sf::Vector2f target, int weapon_id) const;
    void SendDamage(int damage, int object_type, int object_id) const;
    void SendEntity(int object_id, int type, int name, sf::Vector2f position, int creator_id = -1) const;
    void SendMoving(int object_id, int object_type, sf::Vector2f new_pos) const;
    void SendStart(int play_amount) const;

private:
    std::vector<message>& MessOutput;
};



#endif //SERVER_MESSAGECREATOR_H
