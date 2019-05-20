//
// Created by kekor on 09.05.19.
//

#include <srv/MessageCreator.h>

MessageCreator::MessageCreator(std::vector<message> &Outp) :
MessOutput(Outp) {}


void MessageCreator::SendBullet(int bullet_id, int parent_id, sf::Vector2f target, int weapon_id) const {
    message mess;
    mess.set_id(MULTICAST_ID);
    mess.set_flag(ServerMessages::flag::MAKE_BULLET);
    msg::make_bullet *bull = mess.add_bullet();
    bull->set_bullet_id(bullet_id);
    bull->set_parent_id(parent_id);
    bull->set_target_x((int)target.x);
    bull->set_target_y((int)target.y);
    bull->set_weapon_id(weapon_id);
    MessOutput.push_back(mess);
}


void MessageCreator::SendDamage(int damage, int object_type, int object_id) const {
    message mess;
    mess.set_id(MULTICAST_ID);
    mess.set_flag(ServerMessages::flag::MAKE_DAMAGE);
    msg::take_damage *dmg = mess.add_damage();
    dmg->set_damage(damage);
    dmg->set_object_id(object_id);
    dmg->set_object_type(object_type);
    MessOutput.push_back(mess);
}


void MessageCreator::SendEntity(int entity_id, int type, int name, sf::Vector2f position, int creator_id) const {
    message mess;
    mess.set_id(MULTICAST_ID);
    mess.set_flag(ServerMessages::flag::MAKE_ENTITY);
    msg::make_entity *ent = mess.add_entity();
    ent->set_id(entity_id);
    ent->set_type(type);
    ent->set_name(name);
    ent->set_creator_id(creator_id);
    ent->set_x((int)position.x);
    ent->set_y((int)position.y);
    MessOutput.push_back(mess);
}


void MessageCreator::SendMoving(int object_id, int object_type, sf::Vector2f new_pos) const {
    message mess;
    mess.set_id(MULTICAST_ID);
    mess.set_flag(ServerMessages::flag::MAKE_MOVE);
    msg::make_move *ent = mess.add_move();
    ent->set_object_id(object_id);
    ent->set_object_type(object_type);
    ent->set_new_x((int)new_pos.x);
    ent->set_new_y((int)new_pos.y);
    MessOutput.push_back(mess);
}

void MessageCreator::SendStart(int client_id, int play_amount) const {
    message mess;
    mess.set_id(client_id);
    mess.set_flag(ServerMessages::flag::START_GAME);
    msg::start_game *strt = mess.add_start();
    strt->set_players_amount(play_amount);
    MessOutput.push_back(mess);
}
