#include <SFML/Graphics.hpp>

class Cheacker {
private:
   float radius = 40;
public:

   int x{};
   int y{};
   bool isAlive = true;
   bool queen = false;
   sf::Color color;

   void Draw(sf::RenderWindow& window) {
      if (isAlive) {
         sf::CircleShape shape(radius);
         shape.setFillColor(color);
         if (queen) {
            shape.setOutlineThickness(3.f);
            shape.setOutlineColor(sf::Color::Black);
         }
         shape.setPosition(sf::Vector2f(x * 100 + (100 - radius * 2) / 2, y * 100 + (100 - 2 * radius) / 2));
         window.draw(shape);
      }
   }
};