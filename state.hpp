#ifndef FLAPPYBIRD_STATE_HPP
#define FLAPPYBIRD_STATE_HPP

#include <SFML/Graphics.hpp>

class GameEngine;

class State
{
public:
  virtual ~State() = default;

  virtual void init() = 0;

  virtual void handleInput() = 0;
  virtual void update(sf::Time dt) = 0;
  virtual void render() = 0;
};

#endif //FLAPPYBIRD_STATE_HPP
