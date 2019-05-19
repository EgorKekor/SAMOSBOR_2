#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <srv/server.h>
#include <res/secure_queue.h>
#include <res/message.h>
#include <vector>
#include <srv/MessageCreator.h>
#include <res/TextureManager.h>

class GameContext {
public:
    GameContext(sf::RenderWindow &Window_, server &server_);
    const MessageCreator &GetMsgCreator() const { return MsgCreator; };
    const sf::RenderWindow &GetWindow() const { return Window; };

    std::vector<message> &GetMessInput() { return MessInput; };
    std::vector<message> &GetMessOutput() { return MessOutput; };
    server &GetServer() const { return Server; };

private:
    TextureManager textureManager;
    std::vector<message> MessInput;        //  Это не прямые ссылки на контейнер сервера!
    sf::RenderWindow &Window;
    server &Server;
    MessageCreator MsgCreator;
    std::vector<message> MessOutput;    //  Данные вектора заполняются/считываются, а в конце цикла пушатся/читаются на/с сервер!

    sf::View View;
};

#endif
