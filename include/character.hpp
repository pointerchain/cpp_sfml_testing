// charater.hpp

#pragma once

#include "config.hpp"

#include <SFML/Graphics.hpp>

enum class ActionState { Grounded, Jumping, Falling };

struct PlayerInput {
  sf::Vector2f direction;
  bool jump_requested;
};

class Character {
public:
  Character(sf::RenderWindow &window);

  void update(const sf::Time delta_time, const PlayerInput &player_input);
  void draw();

private:
  sf::RenderWindow &window_;
  sf::CircleShape self_{sf::CircleShape(Config::Character::kRadius)};

  sf::Vector2f velocity_{};
  sf::Vector2f distance_{};

  ActionState action_state_{ActionState::Falling};

  sf::Vector2f HandlePhysicsAndInput(const sf::Time delta_time,
                                     const PlayerInput &player_input);
  void HandleStateAndCollisions(sf::Vector2f &next_position);
};