#ifndef FLAPPYBIRD_MAIN_MENU_STATE_HPP
#define FLAPPYBIRD_MAIN_MENU_STATE_HPP

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "game-engine.hpp"

class MainMenuState: public State
{
public:
  explicit MainMenuState(gameDataPtr);

  void init() override;
  void handleInput() override;
  void update(sf::Time dt) override;
  void render() override;

private:
  gameDataPtr data_;

  sf::Sprite background_;
  sf::Sprite title_;
  sf::Sprite playButton_;
};

#endif //FLAPPYBIRD_MAIN_MENU_STATE_HPP
