//
// Anvsar for tegning av skapning. Skal kunne byttes ut lett
//

#ifndef ECO_GRAPHICS_H
#define ECO_GRAPHICS_H

#include <SFML/System.hpp>
//#include "ask/physics.h"

class Graphics
{
public:
  //Ask::Physics::Shape bounds;
  
  virtual void render(Logic &blob_data) = 0;
};

class Graphics_circle : public Graphics
{
public:
//  Ask::Physics::Circle bounds;
  
public:
  Graphics_circle():/*bounds(0, 0, 10),*/ circle(10, 30){}
  
  void render(Logic &blob_data) override
  {
//    circle.setPosition({(float)blob_data.pos.x, (float)blob_data.pos.y});
    
//    bounds.center = blob_data.pos;
    
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
  Graphics_image(){}
  
  void render(Logic &data) override
  {
    static sf::CircleShape circle;
    
    auto pos = data.body->GetPosition();
//    files.simple_blob.setPosition({(float)pixels(pos.x), (float)pixels(pos.y)});
//    files.simple_blob.setRotation(Ask::degrees(data.body->GetAngle()) + 90);

//    window.draw(files.simple_blob);

    circle.setFillColor(sf::Color::White);
    circle.setRadius(data.r);
    circle.setOrigin(data.r, data.r);
    circle.setPosition(pixels(pos.x), pixels(pos.y));
    window.draw(circle);
    
    
//    rect.setSize({r * 2, pixels(ray.length)});
//    rect.setOrigin({r, 0});
//    rect.setRotation(Ask::degrees(ray.angle) - 90.f);
//    rect.setPosition({pixels(ray.source.x), pixels(ray.source.y)});
//    window.draw(rect);

//    b2Vec2 vec = {ray.end.x - ray.start.x, ray.end.y - ray.start.y};
//    vec *= ray.intersection_fraction;

    for (Ray &ray: data.rays)
    {
      static sf::RectangleShape rect;
      float r = 1;
      rect.setSize({r * 2, pixels(ray.length * ray.intersection_fraction)});
      rect.setOrigin({r, 0});
      rect.setRotation(Ask::degrees(ray.angle) - 90);
      rect.setPosition({pixels(ray.start.x), pixels(ray.start.y)});
      window.draw(rect);
    }
    
    if (hitbox_blob)
    {
//      bounds_gfx.setFillColor(data.intersected? hitbox_hit : hitbox_unhit);
//      window.draw(fit_to_bounds(bounds_gfx, bounds));
    }
  }
};

#endif //ECO_GRAPHICS_H
