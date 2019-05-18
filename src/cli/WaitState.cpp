#include "AllStates.h"

#include <arpa/inet.h>

using std::make_unique;
using std::move;
using std::string;
using std::cout;
using std::endl;
using STATE_PTR = std::unique_ptr<State>;

WaitState::WaitState(StateManager *stack, GameContext &context_) : State(stack, context_) {
  font.loadFromFile("../Graphics/font.ttf");
  connectionEstablished = false;
  ipError = false;

  helpText.setPosition(context.windowSize.x - 1600, context.windowSize.y - 1000);
  helpText.setFont(font);
  helpText.setString(std::wstring(L"Введите IP-адресс сервера:"));
  helpText.setCharacterSize(58);
  helpText.setColor(sf::Color::White);

  errorText.setPosition(helpText.getPosition().x, helpText.getPosition().y + 250);
  errorText.setFont(font);
  errorText.setString(std::wstring(L"Не корректный IP, введите еще раз."));
  errorText.setCharacterSize(58);
  errorText.setColor(sf::Color::Red);

  text.setPosition(helpText.getPosition().x, helpText.getPosition().y + 150);
  text.setFont(font);
  text.setCharacterSize(58);
  text.setColor(sf::Color::White);
}

void WaitState::handle_input(sf::Keyboard::Key key, bool isPressed) {
  if ((key == sf::Keyboard::Escape) && (isPressed)) {
    STATE_PTR new_state = make_unique<MenuState>(stack, context);
    push_state(move(new_state));
  } else if (key == sf::Keyboard::Return) {
    if (is_ipv4_address()) {
      ipError = false;
      connectionEstablished = context.Client.connect_to_address(address) == 0;
//      while (true) {
//        if (context.Client.empty()) {
//          continue;
//        }
//        message msg = context.Client.front();
//        context.Client.pop();
//        if (msg.flag == START_FLAG) {
//          break;
//        }
//      }
      if (connectionEstablished) {
        STATE_PTR new_state = make_unique<GameState>(stack, context);
        push_state(move(new_state));
      } else {
        ipError = true;
        address.clear();
      }
    } else {
      ipError = true;
      address.clear();
    }
  }
}
void WaitState::handle_input(sf::Mouse::Button /*mouse*/, bool /*isPressed*/) {

}

void WaitState::draw() {

  context.mWindow->clear();
  context.mWindow->setView(context.view);

  context.mWindow->draw(text);
  context.mWindow->draw(helpText);

  if (ipError) {
    context.mWindow->draw(errorText);
  }
  context.mWindow->display();
}

void WaitState::update(sf::Time /*deltaTime*/) {

}

void WaitState::handle_input(char symbol) {
  if (isdigit(symbol) or symbol == '.') {
    address += static_cast<char>(symbol);
    text.setString(address);
  }

}

bool WaitState::is_ipv4_address() {
  struct sockaddr_in sa{};
  return inet_pton(AF_INET, address.c_str(), &(sa.sin_addr)) != 0;
}
