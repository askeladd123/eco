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

/// husk å kjør static init en gang
class Graphics_image : public Graphics
{
public:
  Ask::Physics::Circle bounds;

public:
  Graphics_image():bounds(0, 0, 10){}
  
  void render(Logic &blob_data) override
  {
    sprite.setPosition({blob_data.x, blob_data.y});
    sprite.setRotation(sf::radians(blob_data.v_angle + M_PI / 2));
    
    bounds.x = blob_data.x;
    bounds.y = blob_data.y;
    
    window.draw(sprite);
  }
  
  static void init()
  {
    if (!texture.loadFromFile("res/blob.png"))
      throw std::runtime_error("Graphics: couldn't load blob.png");
    
    sprite.setTexture(texture);
    sprite.setScale({0.4f, 0.4f});
    sprite.setOrigin({64, 64});
  }

private:
  static sf::Texture texture;
  static sf::Sprite sprite;
};

sf::Texture Graphics_image::texture;
sf::Sprite Graphics_image::sprite;

#endif //ECO_GRAPHICS_H
