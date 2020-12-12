#include <iostream>
#include "game-state.hpp"
#include "game-over-state.hpp"

GameState::GameState(gameDataPtr data):
  data_(std::move(data)),
  state_(GAME_STATE::READY),
  flashOn_(true),
  flashShape_(sf::Vector2f(data_->window_.getSize())),
  score_(0)
{}

void GameState::init()
{
  if(hitSoundBuffer_.loadFromFile(HIT_SOUND_FILEPATH) &&
     wingSoundBuffer_.loadFromFile(WING_SOUND_FILEPATH) &&
     pointSoundBuffer_.loadFromFile(POINT_SOUND_FILEPATH))
  {
    hitSound_.setBuffer(hitSoundBuffer_);
    wingSound_.setBuffer(wingSoundBuffer_);
    pointSound_.setBuffer(pointSoundBuffer_);
  }

  data_->assets_.loadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
  data_->assets_.loadTexture("Land", LAND_FILEPATH);

  data_->assets_.loadTexture("Upper Pipe", UPPER_PIPE_FILEPATH);
  data_->assets_.loadTexture("Lower Pipe", LOWER_PIPE_FILEPATH);
  data_->assets_.loadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);

  data_->assets_.loadTexture("Bird 1", BIRD_1_FILEPATH);
  data_->assets_.loadTexture("Bird 2", BIRD_2_FILEPATH);
  data_->assets_.loadTexture("Bird 3", BIRD_3_FILEPATH);
  data_->assets_.loadTexture("Bird 4", BIRD_4_FILEPATH);

  data_->assets_.loadFont("Flappy Font", FLAPPY_FONT_FILEPATH);
  textScore_.setFont(data_->assets_.getFont("Flappy Font"));
  textScore_.setString("0");
  textScore_.setCharacterSize(128);
  textScore_.setFillColor(sf::Color::White);
  textScore_.setOrigin(textScore_.getGlobalBounds().width / 2, textScore_.getGlobalBounds().height / 2);
  textScore_.setPosition(data_->window_.getSize().x / 2, data_->window_.getSize().y / 7);

  pipe_ = std::make_unique<Pipe>(data_);
  land_ = std::make_unique<Land>(data_);
  bird_ = std::make_unique<Bird>(data_);

  flashShape_.setFillColor(sf::Color(255, 255, 255, 0));

  background_.setTexture(data_->assets_.getTexture("Game Background"));
  background_.setPosition(0, -land_->getSprites().begin()->getGlobalBounds().height);

}

void GameState::handleInput()
{
  sf::Event e{};

  while(data_->window_.pollEvent(e))
  {
    if(sf::Event::Closed == e.type)
    {
      data_->window_.close();
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
      if(sf::IntRect(background_.getGlobalBounds()).contains(sf::Mouse::getPosition(data_->window_)))
      {
        if(state_ != GAME_STATE::GAME_OVER)
        {
          state_ = GAME_STATE::PLAYING;
          bird_->tap();
          wingSound_.play();
        }
      }
    }
  }
}

void GameState::update(sf::Time dt)
{
  if(state_ != GAME_STATE::GAME_OVER)
  {
    bird_->animate(dt.asSeconds());
    land_->move(dt.asSeconds());
  }
  if(state_ == GAME_STATE::PLAYING)
  {
    pipe_->move(dt.asSeconds());

    pipe_->randomizeFrequency();
    if(clock_.getElapsedTime().asSeconds() > pipe_->getFrequency())
    {
      pipe_->randomizeOffset();

      pipe_->spawnScoringPipe();
      pipe_->spawnInvisiblePipe();
      pipe_->spawnLowerPipe();
      pipe_->spawnUpperPipe();

      clock_.restart();
    }
    bird_->update(dt.asSeconds());

    std::vector<sf::Sprite> landSprites = land_->getSprites();
    for(auto & landSprite : landSprites)
    {
      if(isIntersected(bird_->getSprite(), 0.7,  landSprite, 1))
      {
        state_ = GAME_STATE::GAME_OVER;
        clock_.restart();
        hitSound_.play();
      }
    }

    std::vector<sf::Sprite> pipeSprites = pipe_->getSprites();
    for(auto & pipeSprite : pipeSprites)
    {
      if(isIntersected(bird_->getSprite(), 0.625, pipeSprite, 1))
      {
        state_ = GAME_STATE::GAME_OVER;
        clock_.restart();
        hitSound_.play();
      }
    }

    if(state_ == GAME_STATE::PLAYING)
    {
      std::vector<sf::Sprite>& scoringSprites = pipe_->getScoringSprites();
      for(size_t i = 0; i < scoringSprites.size(); ++i)
      {
        if(isIntersected(bird_->getSprite(), 0.625,  scoringSprites[i], 1))
        {
          score_++;
          textScore_.setString(std::to_string(score_));
          scoringSprites.erase(scoringSprites.begin() + i);
          pointSound_.play();
        }
      }
    }
  }
  if(state_ == GAME_STATE::GAME_OVER)
  {
    if(flashOn_)
    {
      auto alpha = flashShape_.getFillColor().a + FLASH_SPEED * dt.asSeconds();
      if(alpha >= 255)
      {
        alpha = 255;
        flashOn_ = false;
      }
      flashShape_.setFillColor(sf::Color(255, 255, 255, alpha));
    }
    else
    {
      auto alpha = flashShape_.getFillColor().a - FLASH_SPEED * dt.asSeconds();
      if(alpha <= 0)
      {
        alpha = 0;
      }
      flashShape_.setFillColor(sf::Color(255, 255, 255, alpha));
    }

    if(clock_.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER)
    {
      wingSound_.~Sound();
      pointSound_.~Sound();
      hitSound_.~Sound();
      wingSoundBuffer_.~SoundBuffer();
      pointSoundBuffer_.~SoundBuffer();
      hitSoundBuffer_.~SoundBuffer();

      data_->states_.pushState(statePtr(std::make_unique<GameOverState>(data_, score_)));
    }
  }
}

void GameState::render()
{
  data_->window_.clear();
  data_->window_.draw(background_);

  pipe_->draw();
  land_->draw();
  bird_->draw();
  data_->window_.draw(flashShape_);
  data_->window_.draw(textScore_);

  data_->window_.display();
}

bool GameState::isIntersected(sf::Sprite sprite1, float scale1, sf::Sprite sprite2, float scale2)
{
  sprite1.setScale(scale1, scale1);
  sprite2.setScale(scale2, scale2);

  return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}
