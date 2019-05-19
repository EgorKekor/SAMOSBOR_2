#ifndef SERVER_STATE_H
#define SERVER_STATE_H

#include <iostream>
#include <memory>
#include <vector>

#include <cli/GameContext.h>

class StateManager;

class State {
 public:
  using STATE_PTR = std::unique_ptr<State>;

  explicit State(StateManager *stack, GameContext &context_);
  virtual ~State() = default;

  virtual void handle_input(sf::Keyboard::Key key, bool isPressed) = 0;
  virtual void handle_input(sf::Mouse::Button mouse, bool isPressed) = 0;
  virtual void handle_input(char symbol) = 0;

  virtual void update(sf::Time deltaTime) = 0;
  virtual void draw() = 0;

 protected:
  void push_state(STATE_PTR &&NewState) const;
  void pop_state() const;

  StateManager *const stack;
  GameContext &context;
 private:

};



#endif //SERVER_STATE_H
