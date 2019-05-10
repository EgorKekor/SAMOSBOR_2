#include "GameContext.h"


GameContext::GameContext(sf::RenderWindow &Window_, server &server_):
Window(Window_), MessInput(server_.GetInput), MessOutput(server_.GetOutput),          // TO_DO(Stepan): Добавить методы в сервер
Server(server_),
MsgCreator() {
    View.reset(sf::FloatRect(0, 0, 1280, 720));
}


