#include "GameContext.h"

GameContext::GameContext(sf::RenderWindow &Window_, vector<message>& Input, vector<message>& Output):
Window(&Window_), MessInput(Input), MessOutput(Output),
Server()
MsgCreator() {
    View_.reset(sf::FloatRect(0, 0, 1280, 720));

}


const MessageCreator& GameContext::GetMsgCreator() {
    return &MsgCreator;
}

const sf::RenderWindow& GameContext::GetWindow() {
    return &Window;
}

vector<message>& GameContext::GetMessInput() {
    return &MessInput;
}

vector<message>& GameContext::GetMessOutput() {
    return &MessOutput;
}
