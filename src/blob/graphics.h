//
// Anvsar for tegning av skapning. Skal kunne byttes ut lett
//

#ifndef ECO_GRAPHICS_H
#define ECO_GRAPHICS_H

#include <SFML/Graphics.hpp>

class Graphics
{
public:
  void render(sf::RenderWindow &window)
  {
    window.draw(sf::CircleShape());
  }
};

#endif //ECO_GRAPHICS_H
