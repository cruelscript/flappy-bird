#ifndef FLAPPYBIRD_GAME_ENGINE_HPP
#define FLAPPYBIRD_GAME_ENGINE_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "state-manager.hpp"
#include "asset-manager.hpp"

struct GameData
{
  sf::RenderWindow window_;
  StateManager states_;
  AssetManager assets_;
};

typedef std::shared_ptr<GameData> gameDataPtr;

class GameEngine
{
public:
  GameEngine(int width, int height, const std::string& title);

private:
  gameDataPtr data_;
  const sf::Time dt = sf::seconds(1.0f / 60.0f);
  sf::Clock clock_;

  void run();
};

#endif //FLAPPYBIRD_GAME_ENGINE_HPP
