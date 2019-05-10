#include "GameEngine.h"


GameEngine::GameEngine(): Window(sf::VideoMode(1280, 720), "SAMOSBOR2", sf::Style::Close),
Server(),
Manager(Server) {}


int GameEngine::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time const TimePerFrame = sf::seconds(1.f / 60.f);
    while (mWindow.isOpen()) {
        handleInput();
        timeSinceLastUpdate += clock.restart();
        if (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate = sf::Time::Zero;
            handleInput();
            update(TimePerFrame);
            //manager.draw();
        }
    }
    running = false;
    return 0;
}


int GameEngine::handleInput() {
    message msg;
    while (!Server.GetInput.empty()) {          //  TO_DO: Сделать на сервере методы Get для входной и выходной очереди
        if (/*Проверить сообщение на завершение*/) {
            mWindow.close();
            quit();
        }
        Manager.handleInput();
    }

    return 0;
}

int GameEngine::update(sf::Time deltaTime) {
    Manager.update(deltaTime);
    return 0;
}

int GameEngine::quit() {
    running == false;
    return 0;
}

bool GameEngine::running() {
    return running;
}

