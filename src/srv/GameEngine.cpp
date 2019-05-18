#include "srv/GameEngine.h"

GameEngine::GameEngine() : Window(sf::VideoMode(1280, 720), "SAMOSBOR2", sf::Style::Close),
                           running(true),
                           Server(),
                           Manager(Window, Server) {}

int GameEngine::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  sf::Time const TimePerFrame = sf::seconds(1.f / 60.f);
  while (running) {
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
  while (!Server.empty()) {
    Manager.handleInput();
  }
  sf::Event event;
  while (Window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      Window.close();
      running = false;
      return 0;
    }
  }
  return 0;
}

int GameEngine::update(sf::Time deltaTime) {
  Manager.update(deltaTime);
  return 0;
}



