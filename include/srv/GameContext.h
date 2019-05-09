#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <server.h>
#include <../res/secure_queue.h>
#include <../res/message.h>
#include <vector>



class GameContext {
 public:
    GameContext(sf::RenderWindow &Window_, std::vector<message>& Input, std::vector<message>& Output);
    const MessageCreator& GetMsgCreator() const;
    const sf::RenderWindow& GetWindow() const;

    std::vector<message>& GetMessInput() const;
    std::vector<message>& GetMessOutput() const;

 private:
    server Server;
    std::MessageCreator MsgCreator;

    std::vector<message>& MessInput;
    std::vector<message>& MessOutput;


    sf::RenderWindow &Window;
    sf::View View;

}

#endif
