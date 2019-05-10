#include "GameEngine.h"


GameEngine::GameEngine(): Window(sf::VideoMode(1280, 720), "SAMOSBOR2", sf::Style::Close),
running(true),
Server(),
Manager(Server) {}


int GameEngine::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time const TimePerFrame = sf::seconds(1.f / 60.f);
    while (Window.isOpen() && running) {
        handleInput();
        timeSinceLastUpdate += clock.restart();
        if (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate = sf::Time::Zero;
            handleInput();
            update(TimePerFrame);
            //manager.draw();
        }
    }
    return 0;
}


int GameEngine::handleInput() {
    message msg;
    while (!Server.GetInput.empty()) {          //  TO_DO: Сделать на сервере методы Get для входной и выходной очереди
        if (/*Проверить сообщение на завершение*/) {
            Window.close();
            running = false;
        } else {
            Manager.handleInput();
        }
    }
    return 0;
}

int GameEngine::update(sf::Time deltaTime) {
    Manager.update(deltaTime);
    return 0;
}



