//
// Anvsar for tegning av skapning. Skal kunne byttes ut lett
//

#ifndef ECO_GRAPHICS_H
#define ECO_GRAPHICS_H

#include "ask/physics.h"

class Graphics
{
public:
  //Ask::Physics::Shape bounds;
  
  virtual void render(Logic &blob_data) = 0;
};

class Graphics_circle : public Graphics
{
public:
  Ask::Physics::Circle bounds;
  
public:
  Graphics_circle():bounds(0, 0, 10), circle(10, 30){}
  
  void render(Logic &blob_data) override
  {
    circle.setPosition(sf::Vector2f(blob_data.x, blob_data.y));
    
    bounds.x = blob_data.x;
    bounds.y = blob_data.y;
    
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
