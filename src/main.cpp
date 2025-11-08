#include <SFML/Graphics.hpp>
#include <cmath>

void draw(sf::RenderWindow &window, const sf::Time delta_time,
          const sf::Vector2f direction, const bool jump_requested) {
  const auto dt_seconds = delta_time.asSeconds();

  static sf::CircleShape circle(40);

  static float y_velocity{0.f};
  static bool in_air{true};

  if (jump_requested && !in_air) {
    in_air = true;
    y_velocity = -1000;
  }

  y_velocity = std::min(y_velocity + dt_seconds * 1540.f, 1740.f);

  float y_distance = y_velocity * dt_seconds;
  float x_distance = direction.x * dt_seconds * 500;

  sf::Vector2f velocity{x_distance, y_distance};

  auto next_position = circle.getPosition() + velocity;

  if (next_position.x < 0) {
    next_position.x = 0;
  } else if (next_position.x + circle.getRadius() * 2 >
             static_cast<float>(window.getSize().x)) {
    next_position.x =
        static_cast<float>(window.getSize().x) - circle.getRadius() * 2;
  }

  if (next_position.y < 0) {
    next_position.y = 0;
    y_velocity = 0;
  } else if (next_position.y + circle.getRadius() * 2 >
             static_cast<float>(window.getSize().y)) {
    next_position.y =
        static_cast<float>(window.getSize().y) - circle.getRadius() * 2;
    y_velocity = 0;
    in_air = false;
  }

  circle.setFillColor(sf::Color::Blue);
  circle.setPosition(next_position);

  window.draw(circle);
}

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "My First Window!");
  sf::Clock clock{};

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
      default:
        break;
      }
    }

    sf::Vector2f direction{};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      direction.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      direction.x += 1;
    }

    const auto jump_requested = sf::Keyboard::isKeyPressed(sf::Keyboard::W);

    const auto magnitude = std::sqrt(static_cast<float>(
        direction.x * direction.x + direction.y * direction.y));
    if (magnitude != 0) {
      direction.x /= magnitude;
      direction.y /= magnitude;
    }

    window.clear();
    draw(window, clock.restart(), direction, jump_requested);
    window.display();
  }

  return 0;
}