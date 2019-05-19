//
// Created by anita on 5/18/19.
//

#ifndef SERVER_MESSAGECREATOR_H
#define SERVER_MESSAGECREATOR_H

#include <cli/client.h>

class MessageCreator {
 public:
  MessageCreator(std::vector<message>& Outp);
  void SendShoting(size_t object_id, size_t object_type, size_t weapon_type, sf::Vector2f position) const;
  void SendMoving(size_t object_id, size_t object_type, size_t direction) const;

 private:
  std::vector<message>& MessOutput;
};

#endif //SERVER_MESSAGECREATOR_H
