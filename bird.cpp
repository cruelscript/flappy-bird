#include "bird.hpp"

Bird::Bird(gameDataPtr data):
  data_(std::move(data)),
  state_(BIRD_STATE::STILL),
  rotation_(0),
  currentFrame(0)
{
  frames_.push_back(data_->assets_.getTexture("Bird 1"));
  frames_.push_back(data_->assets_.getTexture("Bird 2"));
  frames_.push_back(data_->assets_.getTexture("Bird 3"));
  frames_.push_back(data_->assets_.getTexture("Bird 4"));

  bird_.setTexture(frames_[currentFrame]);
  bird_.setPosition(data_->window_.getSize().x / 4.0 - bird_.getGlobalBounds().width / 2.0,
                    data_->window_.getSize().y / 2.0 - bird_.getGlobalBounds().height / 2.0);
  bird_.setOrigin(bird_.getGlobalBounds().width / 2, bird_.getGlobalBounds().height / 2);

}

void Bird::update(float dt)
{
  switch(state_)
  {
  case BIRD_STATE::FAILING:
    bird_.move(0, GRAVITY * dt);
    rotation_ += ROTATION_SPEED * dt;

    if(rotation_ > MAX_ROTATION_VALUE)
    {
      rotation_ = MAX_ROTATION_VALUE;
    }
    bird_.setRotation(rotation_);
    break;

  case BIRD_STATE::FLYING:
    bird_.move(0, -FLYING_SPEED * dt);
    rotation_ -= ROTATION_SPEED * dt;

    if(rotation_ < MAX_ROTATION_VALUE)
    {
      rotation_ = -MAX_ROTATION_VALUE;
    }
    break;

  case BIRD_STATE::STILL:
    break;
  }
  if(movementClock_.getElapsedTime().asSeconds() > FLYING_DURATION)
  {
    movementClock_.restart();
    state_ = BIRD_STATE::FAILING;
  }
}

void Bird::tap()
{
  movementClock_.restart();
  state_ = BIRD_STATE::FLYING;
}

void Bird::draw()
{
  data_->window_.draw(bird_);
}

void Bird::animate(float dt)
{
  if(clock_.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / frames_.size())
  {
    if(currentFrame < frames_.size() - 1)
    {
      currentFrame++;
    }
    else
    {
      currentFrame = 0;
    }
    bird_.setTexture(frames_[currentFrame]);
    clock_.restart();
  }
}

const sf::Sprite& Bird::getSprite() const
{
  return bird_;
}
