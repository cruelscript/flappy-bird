#ifndef FLAPPYBIRD_STATE_MANAGER_HPP
#define FLAPPYBIRD_STATE_MANAGER_HPP

#include <memory>
#include <stack>
#include "state.hpp"

typedef std::unique_ptr<State> statePtr;

class StateManager
{
public:
  void pushState(statePtr state)
  {
    states_.push(std::move(state));
    states_.top()->init();
  }
  statePtr& getCurrentState()
  {
    return states_.top();
  }

private:
  std::stack<statePtr> states_;
};

#endif //FLAPPYBIRD_STATE_MANAGER_HPP
