// charater.cpp

#include "character.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <print>

Character::Character(sf::RenderWindow &window) : window_(window) {

  self_.setFillColor(sf::Color::Blue);
}

void Character::update(const sf::Time delta_time,
                       const PlayerInput &player_input) {

  auto next_position = HandlePhysicsAndInput(delta_time, player_input);
  HandleStateAndCollisions(next_position);
  self_.setPosition(next_position);
}

void Character::draw() { window_.draw(self_); }

sf::Vector2f Character::HandlePhysicsAndInput(const sf::Time delta_time,
                                              const PlayerInput &player_input) {

  if (player_input.jump_requested && action_state_ == ActionState::Grounded) {
    velocity_.y = -Config::Character::kJumpPower;
  }

  if (player_input.direction.x == 0) {
    float deceleration = Config::Character::kMoveSpeed * delta_time.asSeconds();
    if (velocity_.x > 0) {
      velocity_.x = std::max(0.f, velocity_.x - deceleration);
    } else if (velocity_.x < 0) {
      velocity_.x = std::min(0.f, velocity_.x + deceleration);
    }
  } else {
    velocity_.x = std::clamp(
        velocity_.x + player_input.direction.x * delta_time.asSeconds() *
                          Config::Character::kMoveSpeed,
        -Config::Character::kMaxVelocity.x, Config::Character::kMaxVelocity.x);
  }

  velocity_.y =
      std::min(velocity_.y + delta_time.asSeconds() * Config::kGravity,
               Config::Character::kMaxVelocity.y);

  distance_.x = velocity_.x * delta_time.asSeconds();
  distance_.y = velocity_.y * delta_time.asSeconds();

  return self_.getPosition() + distance_;
}

void Character::HandleStateAndCollisions(sf::Vector2f &next_position) {
  if (velocity_.y < 0) {
    action_state_ = ActionState::Jumping;
  } else {
    action_state_ = ActionState::Falling;
  }

  if (next_position.x < 0) {
    next_position.x = 0;
  } else if (next_position.x + self_.getRadius() * 2 >
             static_cast<float>(window_.getSize().x)) {
    next_position.x =
        static_cast<float>(window_.getSize().x) - self_.getRadius() * 2;
  }

  if (next_position.y < 0) {
    next_position.y = 0;
    velocity_.y = 0;
  } else if (next_position.y + self_.getRadius() * 2 >
             static_cast<float>(window_.getSize().y)) {
    next_position.y =
        static_cast<float>(window_.getSize().y) - self_.getRadius() * 2;
    velocity_.y = 0;
    action_state_ = ActionState::Grounded;
  }
}