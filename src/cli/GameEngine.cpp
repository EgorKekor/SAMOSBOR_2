#include "GameEngine.h"

bool GameEngine::running_ = true;

GameEngine::GameEngine() : mWindow(sf::VideoMode(640, 480), "SAMOSBOR", sf::Style::Fullscreen),
                           Context(mWindow),
                           manager(Context) {}

bool GameEngine::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  sf::Time const TimePerFrame = sf::seconds(1.f / 60.f);
  while (mWindow.isOpen()) {
    input();
    timeSinceLastUpdate += clock.restart();
    if (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate = sf::Time::Zero;
      input();
      update(TimePerFrame);
      manager.draw();
    }
  }
  running_ = false;
  return true;
}

bool GameEngine::input() {
  sf::Event event{};
  while (mWindow.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      mWindow.close();
      quit();
    }
    manager.process_events(event);
  }
  return true;
}

bool GameEngine::update(sf::Time deltaTime) {
  manager.update(deltaTime);
  return true;
}

bool GameEngine::running() {
  return running_;
}

void GameEngine::quit() {
  running_ = false;
}