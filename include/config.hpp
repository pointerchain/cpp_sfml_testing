// config.hpp

#include <SFML/System/Vector2.hpp>

namespace Config {
constexpr float kGravity{1540};

namespace Character {
constexpr int kRadius{40};
const sf::Vector2f kMaxVelocity{999999, 1740};
} // namespace Character
} // namespace Config