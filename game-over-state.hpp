#ifndef FLAPPYBIRD_GAME_OVER_STATE_HPP
#define FLAPPYBIRD_GAME_OVER_STATE_HPP

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "game-engine.hpp"

class GameOverState: public State
{
public:
  GameOverState(gameDataPtr, size_t score);

  void init() override;
  void handleInput() override;
  void update(sf::Time dt) override;
  void render() override;

private:
  gameDataPtr data_;

  sf::Sprite background_;
  sf::Sprite gameOverTitle_;
  sf::Sprite gameOverScore_;
  sf::Sprite retryButton_;
  sf::Sprite medal_;

  sf::Text scoreText_;
  sf::Text highScoreText_;

  int score_;
  int highScore_;
};

#endif //FLAPPYBIRD_GAME_OVER_STATE_HPP
