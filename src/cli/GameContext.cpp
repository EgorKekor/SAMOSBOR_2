#include "GameContext.h"

GameContext::GameContext(sf::RenderWindow &wnd) : mWindow(&wnd) {
  View.reset(sf::FloatRect(0, 0, 640, 480));
}
