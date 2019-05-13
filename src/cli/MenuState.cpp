#include <include/cli/MenuState.h>

#include "AllStates.h"

using std::make_unique;
using std::move;
using std::string;
using std::cout;
using std::endl;
using STATE_PTR = std::unique_ptr<State>;

MenuState::MenuState(StateManager *stack, GameContext &context_) : State(stack, context_) {
  buttonTexture.loadFromFile("../Graphics/button.png");
  backgroundTexture.loadFromFile("../Graphics/menu.jpg");

  exitSprite.setTexture(buttonTexture);
  gameSprite.setTexture(buttonTexture);
  backgroundSprite.setTexture(backgroundTexture);
  font.loadFromFile("../Graphics/font.ttf");
}

void MenuState::draw() {
  sf::Vector2u size = context.mWindow->getSize();
  unsigned int windowWidth = size.x;
  unsigned int windowHeight = size.y;

  backgroundSprite.setPosition(0, 0);
  exitSprite.setPosition(windowWidth - 1700, windowHeight - 400);
  gameSprite.setPosition(windowWidth - 1700, windowHeight - 600);

  sf::Text exitText;
  exitText.setPosition(exitSprite.getPosition().x + 150, exitSprite.getPosition().y + 20);
  exitText.setFont(font);
  exitText.setString(std::wstring(L"ВЫХОД"));
  exitText.setCharacterSize(58);
  exitText.setColor(sf::Color::White);

  sf::Text gameText;
  gameText.setPosition(gameSprite.getPosition().x + 150, gameSprite.getPosition().y + 20);
  gameText.setFont(font);
  gameText.setString(std::wstring(L"СТАРТ"));
  gameText.setCharacterSize(58);
  gameText.setColor(sf::Color::White);

  sf::Text helpText;
  helpText.setPosition(gameSprite.getPosition().x + 150, gameSprite.getPosition().y + 20);
  helpText.setFont(font);
  helpText.setString(std::wstring(L"СТАРТ"));
  helpText.setCharacterSize(58);
  helpText.setColor(sf::Color::White);

  menuNum = 0;
  context.mWindow->clear();
  context.mWindow->setView(context.View);

  exitSprite.setColor(sf::Color::White);
  gameSprite.setColor(sf::Color::White);

  if ((gameSprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*context.mWindow).x,
                                                          sf::Mouse::getPosition(*context.mWindow).y)))) {
    gameSprite.setColor(sf::Color(164, 64, 132));
    menuNum = 1;
  } else if ((exitSprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*context.mWindow).x,
                                                                 sf::Mouse::getPosition(*context.mWindow).y)))) {
    exitSprite.setColor(sf::Color(164, 64, 132));
    menuNum = 3;
  }

  context.mWindow->draw(backgroundSprite);
  context.mWindow->draw(exitSprite);
  context.mWindow->draw(gameSprite);

  context.mWindow->draw(exitText);
  context.mWindow->draw(gameText);

  context.mWindow->display();
}

void MenuState::handle_input(sf::Keyboard::Key /*key*/, bool /*isPressed*/) {

}

void MenuState::update(sf::Time /*deltaTime*/) {
  //context.View.reset(sf::FloatRect(0, 0, 1280, 720));
}

void MenuState::handle_input(sf::Mouse::Button mouse, bool isPressed) {
  if (sf::Mouse::Left == mouse && isPressed) {
    if (menuNum == 1) {
      pop_state();
      if (stack->get_states_size() == 0) {
        STATE_PTR new_state = make_unique<WaitState>(stack, context);
        push_state(move(new_state));
      }
    } else if (menuNum == 3) {
      context.mWindow->close();
    }
  }

}
