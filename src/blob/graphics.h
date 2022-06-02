//
// Anvsar for tegning av skapning. Skal kunne byttes ut lett
//

#ifndef ECO_GRAPHICS_H
#define ECO_GRAPHICS_H

class Graphics
{
public:
  Graphics():circle(10, 30){}
  
  void render(Logic &blob_data)
  {
    circle.setPosition(sf::Vector2f(blob_data.x, blob_data.y));
    window.draw(circle);
  }
  
  enum color {WHITE, RED};
  void set_color(color color)
  {
    switch(color)
    {
      case WHITE:
        circle.setFillColor(sf::Color::White);
        return;
        
      case RED:
        circle.setFillColor(sf::Color::Red);
        return;
    }
  }
  
private:
  sf::CircleShape circle;
};

#endif //ECO_GRAPHICS_H
