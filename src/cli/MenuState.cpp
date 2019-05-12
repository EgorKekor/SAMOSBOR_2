#include "AllStates.h"
#include "MenuState.h"

using std::make_unique;
using std::move;
using std::string;
using std::cout;
using std::endl;
using STATE_PTR = std::unique_ptr<State>;

MenuState::MenuState(StateManager *stack, GameContext &context_) : State(stack, context_) {
  buttonTexture.loadFromFile("../Graphics/button.png");
  exitSprite.setTexture(buttonTexture);
  font.loadFromFile("../Graphics/font.ttf");
}

void MenuState::draw() {
  exitSprite.setPosition(0, 0);
  sf::Text exitText;
  exitText.setPosition(exitSprite.getPosition().x + 100, exitSprite.getPosition().y + 10);
  exitText.setFont(font);
  exitText.setString(std::wstring(L"ВЫХОД"));
  exitText.setCharacterSize(35);
  exitText.setColor(sf::Color::White);

  menuNum = 0;
  context.mWindow->clear();
  context.mWindow->setView(context.View);

  exitSprite.setColor(sf::Color::White);
  if ((exitSprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*context.mWindow).x, sf::Mouse::getPosition(*context.mWindow).y)))) {
    exitSprite.setColor(sf::Color(164, 64, 132));
    menuNum = 3;
  }

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    if (menuNum == 3) {context.mWindow->close(); }
  }

  context.mWindow->draw(exitSprite);
  context.mWindow->draw(exitText);
  context.mWindow->display();
}

void MenuState::handle_input(sf::Keyboard::Key /*key*/, bool /*isPressed*/) {
}
void MenuState::update(sf::Time /*deltaTime*/) {
  //context.View.reset(sf::FloatRect(0, 0, 1280, 720));
}
void MenuState::handle_input(sf::Mouse::Button /*mouse*/, bool /*isPressed*/) {
}

