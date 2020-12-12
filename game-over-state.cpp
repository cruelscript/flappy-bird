#include "game-over-state.hpp"

#include <fstream>
#include <iostream>
#include "definitions.hpp"
#include "game-state.hpp"


GameOverState::GameOverState(gameDataPtr data, size_t score):
  data_(data),
  score_(score),
  highScore_(0)
{

}

void GameOverState::init()
{
  std::ifstream in(GAME_OVER_HIGHSCORE_FILEPATH);

  if(in.is_open())
  {
    while(!in.eof())
    {
      in >> highScore_;
    }
  }
  in.close();

  std::ofstream out(GAME_OVER_HIGHSCORE_FILEPATH);
  if(out.is_open())
  {
    if(score_ > highScore_)
    {
      highScore_ = score_;
    }
    out << "\n" << highScore_;
  }
  out.close();

  data_->assets_.loadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
  data_->assets_.loadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
  data_->assets_.loadTexture("Game Over Score", GAME_OVER_SCORE_FILEPATH);

  data_->assets_.loadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
  data_->assets_.loadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
  data_->assets_.loadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
  data_->assets_.loadTexture("Platinum Medal", PLATINUM_MEDAL_FILEPATH);

  background_.setTexture(data_->assets_.getTexture("Game Over Background"));
  gameOverTitle_.setTexture(data_->assets_.getTexture("Game Over Title"));
  gameOverScore_.setTexture(data_->assets_.getTexture("Game Over Score"));
  retryButton_.setTexture(data_->assets_.getTexture("Play Button"));

  gameOverScore_.setPosition((data_->window_.getSize().x - gameOverScore_.getGlobalBounds().width) / 2,
                             (data_->window_.getSize().y - gameOverScore_.getGlobalBounds().height) / 2);
  gameOverTitle_.setPosition((data_->window_.getSize().x - gameOverTitle_.getGlobalBounds().width) / 2,
                             gameOverScore_.getPosition().y - gameOverTitle_.getGlobalBounds().height * 1.2);
  retryButton_.setPosition((data_->window_.getSize().x - retryButton_.getGlobalBounds().width) / 2,
                           gameOverScore_.getPosition().y + gameOverScore_.getGlobalBounds().height + retryButton_.getGlobalBounds().height * 0.2);

  scoreText_.setFont(data_->assets_.getFont("Flappy Font"));
  scoreText_.setString(std::to_string(score_));
  scoreText_.setCharacterSize(56);
  scoreText_.setFillColor(sf::Color::White);
  scoreText_.setOrigin(scoreText_.getGlobalBounds().width / 2, scoreText_.getGlobalBounds().height / 2);
  scoreText_.setPosition(data_->window_.getSize().x / 10 * 7.25, data_->window_.getSize().y / 2.15);

  highScoreText_.setFont(data_->assets_.getFont("Flappy Font"));
  highScoreText_.setString(std::to_string(highScore_));
  highScoreText_.setCharacterSize(56);
  highScoreText_.setFillColor(sf::Color::White);
  highScoreText_.setOrigin(highScoreText_.getGlobalBounds().width / 2, highScoreText_.getGlobalBounds().height / 2);
  highScoreText_.setPosition(data_->window_.getSize().x / 10 * 7.25, data_->window_.getSize().y / 1.78);

  if(static_cast<MEDAL_SCORE>(score_) >= MEDAL_SCORE::PLATINUM )
  {
    medal_.setTexture(data_->assets_.getTexture("Platinum Medal"));
  }
  else if(static_cast<MEDAL_SCORE>(score_) >= MEDAL_SCORE::GOLD )
  {
    medal_.setTexture(data_->assets_.getTexture("Gold Medal"));
  }
  else if(static_cast<MEDAL_SCORE>(score_) >= MEDAL_SCORE::SILVER )
  {
    medal_.setTexture(data_->assets_.getTexture("Silver Medal"));
  }
  else if(static_cast<MEDAL_SCORE>(score_) >= MEDAL_SCORE::BRONZE )
  {
    medal_.setTexture(data_->assets_.getTexture("Bronze Medal"));
  }
  medal_.setPosition(175, 465);
}

void GameOverState::handleInput()
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
      if(sf::IntRect(retryButton_.getGlobalBounds()).contains(sf::Mouse::getPosition(data_->window_)))
      {
        data_->states_.pushState(statePtr(std::make_unique<GameState>(data_)));
      }
    }
  }
}

void GameOverState::update(sf::Time)
{}

void GameOverState::render()
{
  data_->window_.clear();

  data_->window_.draw(background_);
  data_->window_.draw(gameOverTitle_);
  data_->window_.draw(gameOverScore_);
  data_->window_.draw(retryButton_);
  data_->window_.draw(scoreText_);
  data_->window_.draw(highScoreText_);
  data_->window_.draw(medal_);

  data_->window_.display();
}
