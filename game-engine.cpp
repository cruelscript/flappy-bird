#include "game-engine.hpp"

#include <cstdlib>
#include <ctime>
#include "main-menu-state.hpp"

GameEngine::GameEngine(int width, int height, const std::string& title):
  data_(std::make_shared<GameData>())
{
  srand(time(nullptr));
  data_->window_.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
  data_->states_.pushState(statePtr(std::make_unique<MainMenuState>(data_)));

  run();
}

void GameEngine::run()
{
  sf::Time newTime;
  sf::Time frameTime;
  sf::Time accumulator;
  sf::Time currentTime = clock_.getElapsedTime();

  while (data_->window_.isOpen())
  {
    newTime = clock_.getElapsedTime();
    frameTime = newTime - currentTime;

    if(frameTime > sf::seconds(0.25))
    {
      frameTime = sf::seconds(0.25);
    }
    currentTime = newTime;
    accumulator += frameTime;

    while(accumulator >= dt)
    {
      data_->states_.getCurrentState()->handleInput();
      data_->states_.getCurrentState()->update(dt);

      accumulator -= dt;
    }
    data_->states_.getCurrentState()->render();
  }
}
