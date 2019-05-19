//
// Created by anita on 5/18/19.
//

#ifndef SERVER_MESSAGECREATOR_H
#define SERVER_MESSAGECREATOR_H

#include <cli/client.h>

class MessageCreator {
 public:
  explicit MessageCreator(std::vector<message>& Outp);
  void SendMouseCommand(sf::Vector2f mouse_position, bool isPressed) const;
  void SendKeyCommand(size_t key, bool isPressed) const;

 private:
  std::vector<message>& messOutput;
};

#endif //SERVER_MESSAGECREATOR_H
