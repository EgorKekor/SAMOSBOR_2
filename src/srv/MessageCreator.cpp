//
// Created by kekor on 09.05.19.
//

#include <srv/MessageCreator.h>

MessageCreator::MessageCreator(std::vector<message> &Outp) :
MessOutput(Outp) {}


void MessageCreator::SendBullet(size_t id, size_t bullet_id, size_t parent_id, sf::Vector2f target, size_t weapon_id) const {
    message mess;
    mess.set_id(id);
    mess.set_flag(ServerMessages::flag::MAKE_BULLET);
    msg::make_bullet *bull = mess.add_bullet();
    bull->set_bullet_id(bullet_id);
    bull->set_parent_id(parent_id);
    bull->set_target_x(target.x);
    bull->set_target_y(target.y);
    bull->set_weapon_id(weapon_id);
    MessOutput.push_back(mess);
}


void MessageCreator::SendDamage(size_t id, int damage, size_t object_type, size_t object_id) const {
    message mess;
    mess.set_id(id);
    mess.set_flag(ServerMessages::flag::MAKE_DAMAGE);
    msg::take_damage *dmg = mess.add_damage();
    dmg->set_damage(damage);
    dmg->set_object_id(object_id);
    dmg->set_object_type(object_type);
    MessOutput.push_back(mess);
}


void MessageCreator::SendEntity(size_t id, size_t object_id, size_t type, size_t name, sf::Vector2f position, int creator_id) const {
    message mess;
    mess.set_id(id);
    mess.set_flag(ServerMessages::flag::MAKE_ENTITY);
    msg::make_entity *ent = mess.add_entity();
    ent->set_id(object_id);
    ent->set_type(type);
    ent->set_name(name);
    ent->set_creator_id(creator_id);
    ent->set_x(position.x);
    ent->set_y(position.y);
    MessOutput.push_back(mess);
}


void MessageCreator::SendMoving(size_t id, size_t object_id, size_t object_type, sf::Vector2f new_pos) const {
    message mess;
    mess.set_id(id);
    mess.set_flag(ServerMessages::flag::MAKE_MOVE);
    msg::make_move *ent = mess.add_move();
    ent->set_object_id(object_id);
    ent->set_object_type(object_type);
    ent->set_new_x(new_pos.x);
    ent->set_new_y(new_pos.y);
    MessOutput.push_back(mess);
}

void MessageCreator::SendStart() const {
    message mess;
    mess.set_id(ServerMessages::id::MULTICAST);
    mess.set_flag(ServerMessages::flag::START_GAME);
    MessOutput.push_back(mess);
}
