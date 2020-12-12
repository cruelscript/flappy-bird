#ifndef FLAPPYBIRD_BIRD_HPP
#define FLAPPYBIRD_BIRD_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "game-engine.hpp"
#include "definitions.hpp"

class Bird
{
public:
  explicit Bird(gameDataPtr);
  void update(float dt);
  void tap();
  void draw();
  void animate(float dt);

  const sf::Sprite& getSprite() const;

private:
  gameDataPtr data_;

  sf::Clock clock_;
  sf::Clock movementClock_;

  BIRD_STATE state_;
  float rotation_;

  std::vector<sf::Texture> frames_;
  sf::Sprite bird_;
  size_t currentFrame;
};

#endif //FLAPPYBIRD_BIRD_HPP
