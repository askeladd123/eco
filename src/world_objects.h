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
};

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

class Stick : public Line
{
  void render() override
  {
  
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

class Crate : public Box
{
public:
  void render()
  {
  
  }
};

class Circle : public Static_object
{
public:
  Ask::Physics::Circle bounds;
  
public:
  Circle(int x, int y, int r) : bounds({x, y, r}){}
  const Ask::Physics::Shape &getBounds() override
  {
    return bounds;
  }
  
  Ask::Physics::Point getCenter() override
  {
    return bounds.center;
  }
  
  void render() override
  {
    static sf::CircleShape gfx;
    window.draw(fit_to_bounds(gfx, bounds));
  }
};

class Melon : public Circle
{
  void render() override
  {
  
  }
};

class Banana{};
class Water{};

#endif //ECO_WORLD_OBJECTS_H
