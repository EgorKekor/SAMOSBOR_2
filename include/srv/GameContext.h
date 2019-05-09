#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <server.h>
#include <../res/secure_queue.h>
#include <../res/message.h>



class GameContext {
 public:
    GameContext(sf::RenderWindow &Window_, vector<message>& Input, vector<message>& Output);
    const MessageCreator& GetMsgCreator();
    const sf::RenderWindow& GetWindow();

    vector<message>& GetMessInput();
    vector<message>& GetMessOutput();

 private:
    server Server;
    MessageCreator MsgCreator;

    vector<message>& MessInput;
    vector<message>& MessOutput;


    sf::RenderWindow Window;
    sf::View View;

}

#endif
