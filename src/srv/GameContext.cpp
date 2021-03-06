#include "srv/GameContext.h"
#include <SFML/Graphics.hpp>


GameContext::GameContext(sf::RenderWindow &Window_, server &server_):
Window(Window_),
Server(server_),
textureManager(),
MsgCreator(MessOutput) {
    View.reset(sf::FloatRect(0, 0, 1280, 720));
}


