#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <server.h>
#include <../res/secure_queue.h>
#include <../res/message.h>
#include <vector>
#include <MessageCreator.h>



class GameContext {
 public:
    GameContext(sf::RenderWindow &Window_, server &server_);

    MessageCreator& GetMsgCreator() const {return MsgCreator;};
    const sf::RenderWindow& GetWindow() const {return Window;};
    std::vector<message>& GetMessInput() {return MessInput;};
    std::vector<message>& GetMessOutput() const {return MessOutput;};
    server& GetServer() const { return Server;};

 private:
    server &Server;
    MessageCreator MsgCreator;

    std::vector<message> MessInput;        //  Это не прямые ссылки на контейнер сервера!
    std::vector<message> MessOutput;       //  Данные вектора заполняются/считываются, а в конце цикла пушатся/читаются на/с сервер!


    sf::RenderWindow &Window;
    sf::View View;
};

#endif
