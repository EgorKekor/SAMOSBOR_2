#include "cli/Player.h"

void Player::drawObject() {

}

void Player::updateObject(sf::Time deltaTime) {

}

sf::FloatRect Player::getRect() {
  return sf::FloatRect();
}

void Player::handle_actor_input(sf::Mouse::Button /*mouse*/, bool /*isPressed*/) {
  if (mainHero) {
//    sf::Vector2i position = sf::Mouse::getPosition();

  }
}

void Player::handle_actor_input(sf::Keyboard::Key key, bool isPressed) {
  if (mainHero) {
    if (key == sf::Keyboard::W) {
      context.messageCreator.SendKeyCommand(ClientMessages::key::W, isPressed);
    } else if (key == sf::Keyboard::S) {
      context.messageCreator.SendKeyCommand(ClientMessages::key::S, isPressed);
    } else if (key == sf::Keyboard::A) {
      context.messageCreator.SendKeyCommand(ClientMessages::key::A, isPressed);
    } else if (key == sf::Keyboard::D) {
      context.messageCreator.SendKeyCommand(ClientMessages::key::D, isPressed);
    } else if (key == sf::Keyboard::Num1) {
      context.messageCreator.SendKeyCommand(ClientMessages::key::NUM1, isPressed);
    } else if (key == sf::Keyboard::Num2) {
      context.messageCreator.SendKeyCommand(ClientMessages::key::NUM2, isPressed);
    } else if (key == sf::Keyboard::Num3) {
      context.messageCreator.SendKeyCommand(ClientMessages::key::NUM3, isPressed);
    } else if (key == sf::Keyboard::Num4) {
      context.messageCreator.SendKeyCommand(ClientMessages::key::NUM4, isPressed);
    }
  }
}
