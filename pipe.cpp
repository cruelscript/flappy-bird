#include "pipe.hpp"
#include <random>
#include <iostream>

#include "definitions.hpp"

Pipe::Pipe(gameDataPtr data):
  data_(data),
  landHeight_(data->assets_.getTexture("Land").getSize().y),
  yOffset_(0),
  frequency_(0)
{

}

void Pipe::spawnUpperPipe()
{
  sf::Sprite sprite(data_->assets_.getTexture("Lower Pipe"));
  sprite.setPosition(data_->window_.getSize().x, -yOffset_);

  sprites_.push_back(sprite);
}

void Pipe::spawnLowerPipe()
{
  sf::Sprite sprite(data_->assets_.getTexture("Upper Pipe"));

  sprite.setPosition(data_->window_.getSize().x,
                     data_->window_.getSize().y - sprite.getLocalBounds().height - yOffset_);

  sprites_.push_back(sprite);
}

void Pipe::spawnInvisiblePipe()
{
  sf::Sprite sprite(data_->assets_.getTexture("Lower Pipe"));

  sprite.setPosition(data_->window_.getSize().x,-yOffset_);

  sprite.setColor(sf::Color(0, 0, 0, 0));
  sprites_.push_back(sprite);
}

void Pipe::spawnScoringPipe()
{
  sf::Sprite sprite(data_->assets_.getTexture("Scoring Pipe"));

  sprite.setPosition(data_->window_.getSize().x, 0);
  scoringSprites_.push_back(sprite);
}

void Pipe::move(float dt)
{
  for(size_t i = 0; i < sprites_.size(); ++i)
  {
    if(sprites_[i].getPosition().x < 0 - sprites_[i].getLocalBounds().width)
    {
      sprites_.erase(sprites_.begin() + i);
    }
    else
    {
      float movement = PIPE_MOVEMENT_SPEED * dt;
      sprites_[i].move(-movement, 0);
    }
  }
  for(size_t i = 0; i < scoringSprites_.size(); ++i)
  {
    if(scoringSprites_[i].getPosition().x < 0 - scoringSprites_[i].getLocalBounds().width)
    {
      scoringSprites_.erase(scoringSprites_.begin() + i);
    }
    else
    {
      float movement = PIPE_MOVEMENT_SPEED * dt;
      scoringSprites_[i].move(-movement, 0);
    }
  }
}

void Pipe::draw()
{
  for(const auto & sprite: sprites_)
  {
    data_->window_.draw(sprite);
  }
}

void Pipe::randomizeOffset()
{
  yOffset_ = rand() % (landHeight_ + 1);
}

const std::vector<sf::Sprite>& Pipe::getSprites() const
{
  return sprites_;
}

std::vector<sf::Sprite>& Pipe::getScoringSprites()
{
  return scoringSprites_;
}

void Pipe::randomizeFrequency()
{
  frequency_ = 1.2f + static_cast<float>((rand()) / static_cast<float>((RAND_MAX / 1.5)));
}

float Pipe::getFrequency() const
{
  return frequency_;
}
