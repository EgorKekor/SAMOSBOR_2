//
// Created by kekor on 09.05.19.
//

#include <MessageCreator.h>

MessageCreator::MessageCreator(std::vector<message> &Outp) :
MessOutput(Outp) {};


bool MessageCreator::SendBullet(size_t bullet_id, size_t parent_id, sf::Vector2f target, size_t weapon_id) {
    message mess;
    mess.set_id(ServerMessages::action::MAKE_BULLET);
    mess.set_flag(0);
    msg::make_bullet *bull = mess.add_bullet();
    bull->set_bullet_id(bullet_id);
    bull->set_parent_id(parent_id);
    bull->set_target_x(target.x);
    bull->set_target_y(target.y);
    bull->set_weapon_id(weapon_id);
    MessOutput.push_back(mess);
}


bool MessageCreator::SendDamage(int damage, size_t object_type, size_t object_id) {
    message mess;
    mess.set_id(ServerMessages::action::MAKE_DAMAGE);
    mess.set_flag(0);
    msg::take_damage *dmg = mess.add_damage();
    dmg->set_damage(damage);
    dmg->set_object_id(object_id);
    dmg->set_object_type(object_type);
    MessOutput.push_back(mess);
}


bool MessageCreator::SendEntity(size_t id, size_t type, size_t name, sf::Vector2f position, int creator_id) {
    message mess;
    mess.set_id(ServerMessages::action::MAKE_ENTITY);
    mess.set_flag(0);
    msg::make_entity *ent = mess.add_entity();
    ent->set_id = id;
    ent->set_type = type;
    ent->set_name = name;
    ent->set_creator_id
}