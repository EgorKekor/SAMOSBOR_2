#include "GameContext.h"
#include <vector>

GameContext::GameContext(sf::RenderWindow &Window_, std::vector<message>& Input, std::vector<message>& Output):
Window(&Window_), MessInput(Input), MessOutput(Output),
Server()
MsgCreator() {
    View.reset(sf::FloatRect(0, 0, 1280, 720));
}


const GameContext::MessageCreator& GameContext::GetMsgCreator() const {
    return &MsgCreator;
}

const sf::RenderWindow& GameContext::GetWindow() const {
    return Window;
}

std::vector<message>& GameContext::GetMessInput() const {
    return MessInput;
}

std::vector<message>& GameContext::GetMessOutput() const {
    return MessOutput;
}
