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
    circle.setPosition(sf::Vector2f(blob_data.x, blob_data.y));
    
    bounds.center.x = blob_data.x;
    bounds.center.y = blob_data.y;
    
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
  sf::CircleShape bounds_gfx;

public:
  Graphics_image():bounds(0, 0, 10){}
  
  void render(Logic &blob_data) override
  {
    sprite.setPosition({blob_data.x, blob_data.y});
    sprite.setRotation(Ask::degrees(blob_data.v_angle + M_PI / 2));

    bounds.center.x = blob_data.x;
    bounds.center.y = blob_data.y;

    window.draw(sprite);
    
    if (hitbox_blob)
      window.draw(fit_to_bounds(bounds_gfx, bounds));
  }
  
  static void init()
  {
    if (!texture.loadFromFile("res/blob.png"))
      throw std::runtime_error("Graphics: couldn't load blob.png");
    
    sprite.setTexture(texture);
    sprite.setScale({0.2f, 0.2f});
    sprite.setOrigin({64, 64});
  }

private:
  static sf::Texture texture;
  static sf::Sprite sprite;
};

sf::Texture Graphics_image::texture;
sf::Sprite Graphics_image::sprite;

#endif //ECO_GRAPHICS_H
