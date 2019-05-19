//
// Created by anita on 5/18/19.
//

#ifndef SERVER_MESSAGECREATOR_H
#define SERVER_MESSAGECREATOR_H

#include <cli/client.h>

class MessageCreator {
 public:
  MessageCreator(std::vector<message>& Outp);
  void SendMouseCommand(sf::Vector2f mouse_position) const;
  void SendKeyCommand(size_t key) const;

 private:
  std::vector<message>& MessOutput;
};

#endif //SERVER_MESSAGECREATOR_H
