#ifndef FLAPPYBIRD_GAME_STATE_HPP
#define FLAPPYBIRD_GAME_STATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "state.hpp"
#include "game-engine.hpp"
#include "pipe.hpp"
#include "land.hpp"
#include "bird.hpp"

class GameState: public State
{
public:
  explicit GameState(gameDataPtr);

  void init() override;
  void handleInput() override;
  void update(sf::Time dt) override;
  void render() override;

private:
  gameDataPtr data_;
  sf::Clock clock_;
  sf::Sprite background_;
  GAME_STATE state_;

  std::unique_ptr<Pipe> pipe_;
  std::unique_ptr<Land> land_;
  std::unique_ptr<Bird> bird_;

  bool flashOn_;
  sf::RectangleShape flashShape_;

  size_t score_;
  sf::Text textScore_;

  sf::SoundBuffer hitSoundBuffer_;
  sf::SoundBuffer wingSoundBuffer_;
  sf::SoundBuffer pointSoundBuffer_;
  sf::Sound hitSound_;
  sf::Sound wingSound_;
  sf::Sound pointSound_;

  static bool isIntersected(sf::Sprite, float scale1, sf::Sprite, float scale2);
};

#endif //FLAPPYBIRD_GAME_STATE_HPP
