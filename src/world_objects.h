//
// Created by askso on 09/06/2022.
//

#ifndef ECO_WORLD_OBJECTS_H
#define ECO_WORLD_OBJECTS_H

#include <SFML/Graphics.hpp>
#include "ask/physics.h"
#include "ask/praktisk.h"

class Static_object
{
public:
  virtual const Ask::Physics::Shape &getBounds() = 0;
  virtual Ask::Physics::Point getCenter() = 0;
  virtual void render() = 0;
  
protected:
  Static_object()
  {
    bounds_circle_gfx.setFillColor(hitbox_unhit);
  }
  
protected:
  static sf::CircleShape bounds_circle_gfx; // TODO: må initialiseres?
};
sf::CircleShape Static_object::bounds_circle_gfx;

class Line : public Static_object
{
public:
  Ask::Physics::Line bounds;
  
public:
  const Ask::Physics::Shape &getBounds() override
  {
    return bounds;
  }
  
  Ask::Physics::Point getCenter() override
  {
    return {bounds.a.x + (bounds.b.x - bounds.a.x) / 2, bounds.a.x + (bounds.b.x - bounds.a.x) / 2};
  }
  
  void render() override
  {
  
  }
};

class Circle : public Static_object
{
public:
  Ask::Physics::Circle bounds;

protected:
  Circle(int x, int y, int r) : bounds({x, y, r}){}
  const Ask::Physics::Shape &getBounds() override
  {
    return bounds;
  }
  
  Ask::Physics::Point getCenter() override
  {
    return bounds.center;
  }
};

class Box : public Static_object
{
public:
  Ask::Physics::Box bounds;
  const Ask::Physics::Shape &getBounds() override
  {
    return bounds;
  }
  
  Ask::Physics::Point getCenter() override
  {
    return bounds.center;
  }
  
  void render()
  {
  
  }
};

class Stick : public Line
{
  void render() override
  {
  
  }
};

class Crate : public Box
{
public:
  void render()
  {
  
  }
};

class Melon : public Circle
{
public:
  Melon(int x, int y, int r) : Circle(x, y, r){}
  
  void render() override
  {
    static sf::CircleShape circle_gfx;
    window.draw(fit_to_bounds(circle_gfx, bounds));
    if (hitbox_static_objects)
      window.draw(fit_to_bounds(bounds_circle_gfx, bounds));
  }
};

class Banana{};
class Water{};

#endif //ECO_WORLD_OBJECTS_H
