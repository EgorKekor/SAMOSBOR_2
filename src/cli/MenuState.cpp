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
  backgroundSprite.setTexture(backgroundTexture);
  // backgroundSprite.setPosition(0, 0);
  font.loadFromFile("../Graphics/font.ttf");

  helpSprite.setTexture(buttonTexture);
  helpSprite.setPosition(context.windowSize.x - 1700, context.windowSize.y - 700);

  exitSprite.setTexture(buttonTexture);
  exitSprite.setPosition(context.windowSize.x - 1700, context.windowSize.y - 550);

  gameSprite.setTexture(buttonTexture);
  gameSprite.setPosition(context.windowSize.x - 1700, context.windowSize.y - 850);

  exitText.setPosition(exitSprite.getPosition().x + 150, exitSprite.getPosition().y + 20);
  exitText.setFont(font);
  exitText.setString(std::wstring(L"ВЫХОД"));
  exitText.setCharacterSize(58);
  exitText.setColor(sf::Color::White);

  gameText.setPosition(gameSprite.getPosition().x + 155, gameSprite.getPosition().y + 20);
  gameText.setFont(font);
  gameText.setString(std::wstring(L"СТАРТ"));
  gameText.setCharacterSize(58);
  gameText.setColor(sf::Color::White);

  helpText.setPosition(helpSprite.getPosition().x + 125, helpSprite.getPosition().y + 20);
  helpText.setFont(font);
  helpText.setString(std::wstring(L"ПОМОЩЬ"));
  helpText.setCharacterSize(58);
  helpText.setColor(sf::Color::White);
}

void MenuState::draw() {
  menuNum = 0;
  context.mWindow->clear();
  context.mWindow->setView(context.view);

  exitSprite.setColor(sf::Color::White);
  gameSprite.setColor(sf::Color::White);
  helpSprite.setColor(sf::Color::White);

  if ((gameSprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*context.mWindow).x,
                                                          sf::Mouse::getPosition(*context.mWindow).y)))) {
    gameSprite.setColor(sf::Color(164, 64, 132));
    menuNum = 1;
  } else if ((helpSprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*context.mWindow).x,
                                                                 sf::Mouse::getPosition(*context.mWindow).y)))) {
    helpSprite.setColor(sf::Color(164, 64, 132));
    menuNum = 2;
  } else if ((exitSprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*context.mWindow).x,
                                                                 sf::Mouse::getPosition(*context.mWindow).y)))) {
    exitSprite.setColor(sf::Color(164, 64, 132));
    menuNum = 3;
  }

  //context.mWindow->draw(backgroundSprite);
  context.mWindow->draw(exitSprite);
  context.mWindow->draw(gameSprite);
  context.mWindow->draw(helpSprite);

  context.mWindow->draw(exitText);
  context.mWindow->draw(gameText);
  context.mWindow->draw(helpText);

  context.mWindow->display();
}

void MenuState::handle_input(sf::Keyboard::Key /*key*/, bool /*isPressed*/) {

}

void MenuState::update(sf::Time /*deltaTime*/) {
  //context.view.reset(sf::FloatRect(0, 0, 1280, 720));
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
void MenuState::handle_input(char /*symbol*/) {

}
