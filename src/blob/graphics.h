//
// Anvsar for tegning av skapning. Skal kunne byttes ut lett
//

#ifndef ECO_GRAPHICS_H
#define ECO_GRAPHICS_H

#include <SFML/System.hpp>
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
    circle.setPosition({(float)blob_data.pos.x, (float)blob_data.pos.y});
    
    bounds.center = blob_data.pos;
    
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

/// husk å kjør static init en gang
class Graphics_image : public Graphics
{
public:
  Ask::Physics::Circle bounds;

public:
  Graphics_image():bounds(0, 0, 10){}
  
  void render(Logic &blob_data) override
  {
    static sf::CircleShape bounds_gfx;
    
    files.simple_blob.setPosition({(float)blob_data.pos.x, (float)blob_data.pos.y});
    files.simple_blob.setRotation(Ask::degrees(atan2(blob_data.vel.y, blob_data.vel.x) + M_PI / 2));

    bounds.center = blob_data.pos;

    window.draw(files.simple_blob);
    
    if (hitbox_blob)
    {
      bounds_gfx.setFillColor(blob_data.intersected? hitbox_hit : hitbox_unhit);
      window.draw(fit_to_bounds(bounds_gfx, bounds));
    }
  }
};

#endif //ECO_GRAPHICS_H
