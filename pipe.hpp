#ifndef FLAPPYBIRD_PIPE_HPP
#define FLAPPYBIRD_PIPE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "game-engine.hpp"

class Pipe
{
public:
  explicit Pipe(gameDataPtr);

  void spawnUpperPipe();
  void spawnLowerPipe();
  void spawnInvisiblePipe();
  void spawnScoringPipe();
  void move(float dt);
  void draw();
  void randomizeOffset();
  void randomizeFrequency();
  float getFrequency() const;

  const std::vector<sf::Sprite>& getSprites() const;
  std::vector<sf::Sprite>& getScoringSprites();
private:
  gameDataPtr data_;
  std::vector<sf::Sprite> sprites_;
  std::vector<sf::Sprite> scoringSprites_;

  size_t landHeight_;
  float yOffset_;
  float frequency_;

};

#endif //FLAPPYBIRD_PIPE_HPP
