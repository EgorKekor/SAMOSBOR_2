#include <include/cli/WaitState.h>

#include "AllStates.h"

using std::make_unique;
using std::move;
using std::string;
using std::cout;
using std::endl;
using STATE_PTR = std::unique_ptr<State>;

WaitState::WaitState(StateManager *stack, GameContext &context_) : State(stack, context_) {
  font.loadFromFile("../Graphics/font.ttf");
}
void WaitState::handle_input(sf::Keyboard::Key key, bool isPressed) {
  if ((key == sf::Keyboard::Escape) && (isPressed)) {
    STATE_PTR new_state = make_unique<MenuState>(stack, context);
    push_state(move(new_state));
  }
}
void WaitState::handle_input(sf::Mouse::Button /*mouse*/, bool /*isPressed*/) {

}

void WaitState::draw() {
  sf::Text gameText;
  gameText.setPosition(0, 0);
  gameText.setFont(font);
  gameText.setString(std::wstring(L"WAIT"));
  gameText.setCharacterSize(58);
  gameText.setColor(sf::Color::White);

  context.mWindow->clear();
  context.mWindow->setView(context.View);
  context.mWindow->draw(gameText);
  context.mWindow->display();
}

void WaitState::update(sf::Time /*deltaTime*/) {

}

