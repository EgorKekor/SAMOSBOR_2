#include "cli/GameContext.h"

GameContext::GameContext(sf::RenderWindow &wnd) : mWindow(&wnd), messageCreator(messOutput) {
  view.reset(sf::FloatRect(0, 0, 1920, 1080));
  windowSize = mWindow->getSize();
}
