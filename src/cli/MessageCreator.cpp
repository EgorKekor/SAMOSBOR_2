#include "cli/MessageCreator.h"
#include "cli/AllGameObjects.h"
#include "res/message.h"

MessageCreator::MessageCreator(std::vector<message>& Outp) :
    messOutput(Outp) {}


void MessageCreator::SendMouseCommand(sf::Vector2f mouse_position, bool isPressed) const {
  message mess;
  mess.set_flag(ClientMessages::flag::MOUSE_PRESSED);
  msg::client_mouse *mouse = mess.add_mouse();
  mouse->set_mouse_x((int)mouse_position.x);
  mouse->set_mouse_y((int)mouse_position.y);
  mouse->set_is_pressed(isPressed);
  messOutput.push_back(mess);
}

void MessageCreator::SendKeyCommand(size_t key, bool isPressed) const {
  message mess;
  mess.set_flag(ClientMessages::flag::KEY_PRESSED);
  msg::client_key *clientKey = mess.add_key();
  clientKey->set_key(key);
  clientKey->set_is_pressed(isPressed);
  messOutput.push_back(mess);
}
