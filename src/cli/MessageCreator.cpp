#include "cli/MessageCreator.h"
#include "cli/AllGameObjects.h"

MessageCreator::MessageCreator(std::vector<message> &Outp) :
    MessOutput(Outp) {}


void MessageCreator::SendMouseCommand(sf::Vector2f mouse_position) const{
  message mess;
  mess.set_flag(ClientMessages::flag::MOUSE_PRESSED);
  msg::client_mouse *mouse = mess.add_mouse();
  mouse->set_mouse_x(mouse_position.x);
  mouse->set_mouse_y(mouse_position.y);
  MessOutput.push_back(mess);
}
void MessageCreator::SendKeyCommand(size_t key) const{
  message mess;
  mess.set_flag(ClientMessages::flag::KEY_PRESSED);
  msg::client_key *clientKey = mess.add_key();
  clientKey->set_key(key);
  MessOutput.push_back(mess);
}
