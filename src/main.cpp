// main.cpp

#include "character.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "My First Window!");
  sf::Clock clock{};
  Character character(window);

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

    character.update(clock.restart(), {direction, jump_requested});
    character.draw();

    window.display();
  }

  return 0;
}