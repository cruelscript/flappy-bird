#ifndef FLAPPYBIRD_LAND_HPP
#define FLAPPYBIRD_LAND_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "game-engine.hpp"

class Land
{
public:
  explicit Land(gameDataPtr);
  void move(float dt);
  void draw();

  const std::vector<sf::Sprite>& getSprites() const;

private:
  gameDataPtr data_;
  std::vector<sf::Sprite> sprites_;
};

#endif //FLAPPYBIRD_LAND_HPP
