//
// Anvsar for tegning av skapning. Skal kunne byttes ut lett
//

#ifndef ECO_GRAPHICS_H
#define ECO_GRAPHICS_H

#include <SFML/Graphics.hpp>

class Graphics
{
public:
  Graphics():circle(10, 30){}
  
  void render(sf::RenderWindow &window, Logic &blob_data)
  {
    circle.setPosition(sf::Vector2f(blob_data.x, blob_data.y));
    window.draw(circle);
  }
  
private:
  sf::CircleShape circle;
};

#endif //ECO_GRAPHICS_H
