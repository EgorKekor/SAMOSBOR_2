#ifndef SERVER_STATEMANAGER_H
#define SERVER_STATEMANAGER_H

#include <iostream>
#include <vector>
#include <memory>

#include "State.h"
#include "GameContext.h"


class StateManager {
  using STATE_PTR = std::unique_ptr<State>;
 public:
  explicit StateManager(GameContext &context);

  void process_events(const sf::Event &event);
  void update(sf::Time deltaTime);
  void draw();

  STATE_PTR &get_state();
  void push_state(STATE_PTR &&new_state);
  void pop_state();

  size_t get_states_size();

 private:
  std::vector<STATE_PTR> StatesStack;
  std::vector<STATE_PTR> StatesBuf;
  GameContext &Context;
};

#endif //SERVER_STATEMANAGER_H
