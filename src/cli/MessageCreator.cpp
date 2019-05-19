#include "cli/MessageCreator.h"
MessageCreator::MessageCreator(std::vector<message> &Outp) :
    MessOutput(Outp) {}

void MessageCreator::SendShoting(size_t /*object_id*/, size_t /*object_type*/, size_t /*weapon_type*/, sf::Vector2f /*position*/) const {

}
void MessageCreator::SendMoving(size_t /*object_id*/, size_t /*object_type*/, size_t /*direction*/) const {

}