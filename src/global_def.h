//
// Created by askso on 31/05/2022.
//

#ifndef ECO_GLOBAL_DEF_H
#define ECO_GLOBAL_DEF_H

#include <SFML/Graphics.hpp>
#include <fstream>

#include "ask/physics.h"
#include "ask/praktisk.h"
#include "ask/workflow.h"

class fps
{
public:
  int get()
  {
    return value;
  }
  
  int normal()
  {
    return value = normal_fps;
  }
  
  int increased()
  {
    if (value == min_fps)
      return value = normal_fps;
    
    else
      return value = max_fps;
  }
  
  int decreased()
  {
    if (value == max_fps)
      return value = normal_fps;
    
    else
      return value = min_fps;
  }

private:
  int value = normal_fps;
  int min_fps = 15;
  int normal_fps = 60;
  int max_fps = 120;
};

void view_resize()
{
  float ratio = (float)window.getSize().x / window.getSize().y;
  view.setSize(sf::Vector2f(view_height * ratio, view_height));
}

//sf::Vector2f mouse()
//{
//  return window.mapPixelToCoords(sf::Mouse::getPosition(window));
//}

#define mouse window.mapPixelToCoords(sf::Mouse::getPosition(window))

//sf::Sprite &fit_to_bounds(sf::Sprite &fit_this, const Ask::Physics::Tile &to_this)
//{
//  fit_this.setOrigin(0, 0);
//  fit_this.setPosition(to_this.center.x - to_this.r_x, to_this.center.y - to_this.r_y);
//  fit_this.setScale(2, 1);
//  return fit_this;
//}

/// sørger for at firkanten du tegner er hitboxen
sf::RectangleShape &fit_to_bounds(sf::RectangleShape &fit_this, const Ask::Physics::Tile &to_this)
{
  fit_this.setSize({(float)to_this.r_x * 2, (float)to_this.r_y * 2});
  fit_this.setOrigin({(float)to_this.r_x, (float)to_this.r_y});
  fit_this.setPosition({(float)to_this.center.x, (float)to_this.center.y});
  return fit_this;
}

sf::RectangleShape &fit_to_bounds(sf::RectangleShape &fit_this, const Ask::Physics::Ray &to_this)
{
  fit_this.setSize({6, to_this.dir.length()});
  fit_this.setOrigin(fit_this.getSize().x / 2, 0);
  fit_this.setPosition(to_this.center.x, to_this.center.y);
  fit_this.setRotation(Ask::degrees(to_this.dir.angle()));
  return fit_this;
}

/// sørger for at sirkelen du tegner er hitboxen
sf::CircleShape &fit_to_bounds(sf::CircleShape &fit_this, const Ask::Physics::Circle &to_this)
{
  fit_this.setRadius(to_this.r);
  fit_this.setOrigin({fit_this.getRadius(), fit_this.getRadius()});
  fit_this.setPosition({(float)to_this.center.x, (float)to_this.center.y});
  return fit_this;
}

/// sørger for at sirkelen du tegner er hitboxen
sf::Vertex *fit_to_bounds(sf::Vertex fit_this[], const Ask::Physics::Line &to_this)
{
  fit_this[0].position.x = to_this.a.x;
  fit_this[0].position.y = to_this.a.y;
  fit_this[1].position.x = to_this.a.x;
  fit_this[1].position.y = to_this.a.y;
  return fit_this;
}

/// sørger for at sirkelen du tegner er hitboxen
sf::Vertex *fit_to_bounds(sf::Vertex fit_this[], const Ask::Physics::Ray &to_this)
{
  fit_this[0].position.x = to_this.center.x;
  fit_this[0].position.y = to_this.center.y;
  fit_this[1].position.x = to_this.center.x + to_this.dir.x;
  fit_this[1].position.y = to_this.center.y + to_this.dir.y;
  return fit_this;
}



#endif //ECO_GLOBAL_DEF_H
