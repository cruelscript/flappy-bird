#include <iostream>
#include "land.hpp"
#include "definitions.hpp"

Land::Land(gameDataPtr data):
  data_(std::move(data))
{
  sf::Sprite sprite(data_->assets_.getTexture("Land"));
  sf::Sprite nextSprite(data_->assets_.getTexture("Land"));

  sprite.setPosition(0, data_->window_.getSize().y - sprite.getGlobalBounds().height);
  nextSprite.setPosition(sprite.getGlobalBounds().width, data_->window_.getSize().y - nextSprite.getGlobalBounds().height);

  sprites_.push_back(sprite);
  sprites_.push_back(nextSprite);
}

void Land::move(float dt)
{
  for(auto & sprite : sprites_)
  {
    float movement = PIPE_MOVEMENT_SPEED * dt;
    sprite.move(-movement, 0);
    if(sprite.getPosition().x < 0 - sprite.getGlobalBounds().width)
    {
      sprite.setPosition(data_->window_.getSize().x, sprite.getPosition().y);
    }
  }
}

void Land::draw()
{
  for(auto & sprite : sprites_)
  {
    data_->window_.draw(sprite);
  }
}

const std::vector<sf::Sprite>& Land::getSprites() const
{
  return sprites_;
}
