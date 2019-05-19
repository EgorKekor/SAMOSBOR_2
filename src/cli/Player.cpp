#include "cli/Player.h"

Player::Player(GameContext &context_, sf::Vector2f position, size_t id_) :
    GameObject(context_, position, id_) {
  type = Entityes::type::PLAYER;
  health = 1000;
  circle.setFillColor(sf::Color{ 0x006495FF });
}

void Player::drawObject() {
  setPlayerView(x, y);
  circle.setPosition({ x, y });
  context.mWindow->draw(circle);
}

void Player::updateObject() {

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
      isMovingUp = isPressed;
      context.messageCreator.SendKeyCommand(ClientMessages::key::W, isPressed);
    } else if (key == sf::Keyboard::S) {
      isMovingLeft = isPressed;
      context.messageCreator.SendKeyCommand(ClientMessages::key::S, isPressed);
    } else if (key == sf::Keyboard::A) {
      isMovingDown = isPressed;
      context.messageCreator.SendKeyCommand(ClientMessages::key::A, isPressed);
    } else if (key == sf::Keyboard::D) {
      isMovingRight = isPressed;
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

void Player::setPlayerView(float x, float y) {
  float tempX = x /*+ width/2*/;
  float tempY = y /*+ height/2*/;
  context.view.setCenter(tempX, tempY);
  context.mWindow->setView(context.view);
}


