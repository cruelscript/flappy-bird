#include <iostream>
#include "main-menu-state.hpp"
#include "game-state.hpp"

MainMenuState::MainMenuState(gameDataPtr data):
  data_(std::move(data))
{}

void MainMenuState::init()
{
  data_->assets_.loadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
  data_->assets_.loadTexture("Game Title", GAME_TITLE_FILEPATH);
  data_->assets_.loadTexture("Play Button", PLAY_BUTTON_FILEPATH);

  background_.setTexture(data_->assets_.getTexture("Main Menu Background"));
  title_.setTexture(data_->assets_.getTexture("Game Title"));
  playButton_.setTexture(data_->assets_.getTexture("Play Button"));

  title_.setPosition((SCREEN_WIDTH / 2) - (title_.getGlobalBounds().width / 2),
                     title_.getGlobalBounds().height / 2);

  playButton_.setPosition((SCREEN_WIDTH / 2) - (playButton_.getGlobalBounds().width / 2),
                          (SCREEN_HEIGHT / 2) - (playButton_.getGlobalBounds().height / 2));
}

void MainMenuState::handleInput()
{
  sf::Event e{};

  while(data_->window_.pollEvent(e))
  {
    if(sf::Event::Closed == e.type)
    {
      data_->window_.close();
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      if(sf::IntRect(playButton_.getGlobalBounds()).contains(sf::Mouse::getPosition(data_->window_)))
      {
        data_->states_.pushState(statePtr(std::make_unique<GameState>(data_)));
      }
    }
  }
}

void MainMenuState::update(sf::Time)
{}

void MainMenuState::render()
{
  data_->window_.clear();

  data_->window_.draw(background_);
  data_->window_.draw(title_);
  data_->window_.draw(playButton_);

  data_->window_.display();
}
