// config.hpp

#include <SFML/System/Vector2.hpp>

namespace Config {
constexpr float kGravity{3000};

namespace Character {
constexpr int kRadius{40};
const float kMoveSpeed{5000};
const float kJumpPower{1500};
const sf::Vector2f kMaxVelocity{1000, 2000};
} // namespace Character
} // namespace Config