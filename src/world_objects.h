//
// Created by askso on 09/06/2022.
//

#ifndef ECO_WORLD_OBJECTS_H
#define ECO_WORLD_OBJECTS_H

#include <SFML/Graphics.hpp>
//#include "ask/physics.h"
#include "ask/matte.h"

class Static_object
{
public:
  bool intersected = false;
  
public:
//  virtual const Ask::Physics::Shape &getBounds() = 0;
//  virtual Ask::Physics::Point getCenter() = 0;
  virtual void render() = 0;

protected:
  Static_object(){}
  virtual void hitbox() = 0;
};

class Line : public Static_object
{
public:
//  Ask::Physics::Line bounds;

protected:
//  Line(Ask::Physics::Line line) :
//  bounds(line),
//  bounds_gfx{
//    {{(float)line.a.x, (float)line.a.y}},
//    {{(float)line.b.x, (float)line.b.y}}}{}
  
public:
//  const Ask::Physics::Shape &getBounds() override { return bounds; }
  
//  Ask::Physics::Point getCenter() override
//  {
//    return {bounds.a.x + (bounds.b.x - bounds.a.x) / 2, bounds.a.x + (bounds.b.x - bounds.a.x) / 2};
//  }

protected:
  void hitbox() override
  {
    auto &color = intersected? hitbox_hit : hitbox_unhit;
    bounds_gfx[0].color = color;
    bounds_gfx[1].color = color;
    window.draw(bounds_gfx, 2, sf::Lines);
  }
  
private:
  sf::Vertex bounds_gfx[2];
};

class Gay : public Static_object
{
public:
//  Ask::Physics::Ray bounds;

protected:
//  Ray(Ask::Physics::Ray ray) :
//  bounds(ray),
//  bounds_gfx{
//      {{(float)ray.center.x, (float)ray.center.y}},
//      {{(float)ray.center.x + ray.dir.x, (float)ray.center.y + ray.dir.y}}}{}

public:
//  const Ask::Physics::Shape &getBounds() override { return bounds; }
  
//  Ask::Physics::Point getCenter() override
//  {
//    return bounds.center;
//  }

protected:
  void hitbox() override
  {
    auto &color = intersected? hitbox_hit : hitbox_unhit;
    bounds_gfx[0].color = color;
    bounds_gfx[1].color = color;
    window.draw(bounds_gfx, 2, sf::Lines);
  }

private:
  sf::Vertex bounds_gfx[2];
};

class Circle : public Static_object
{
public:
//  Ask::Physics::Circle bounds;

protected:
//  Circle(Ask::Physics::Circle circle) : bounds(circle){ fit_to_bounds(bounds_gfx, bounds); }
  
public:
//  const Ask::Physics::Shape &getBounds() override { return bounds; }
//  Ask::Physics::Point getCenter() override
//  {
//    return bounds.center;
//  }

protected:
  void hitbox()
  {
    bounds_gfx.setFillColor(intersected? hitbox_hit : hitbox_unhit);
    window.draw(bounds_gfx);
  }
  
private:
  sf::CircleShape bounds_gfx;
};
//
//class Box : public Static_object
//{
//public:
//  Ask::Physics::Box bounds;
//  const Ask::Physics::Shape &getBounds() override { return bounds; }
//
//  Ask::Physics::Point getCenter() override
//  {
//    return bounds.center;
//  }
//};

class Stick : public Line
{
public:
//  Stick(int x1, int y1, int x2, int y2) : Line({x1, y1, x2, y2}){}
  
  void render() override
  {
    if (hitbox_static_objects)
      hitbox();
  }
};

//class Crate : public Box
//{
//public:
//  void render()
//  {
//
//  }
//};

class Melon : public Circle
{
public:
//  Melon(int x, int y, int r) : Circle({x, y, r}){}
  
  void render() override
  {
    static sf::CircleShape circle_gfx;
//    window.draw(fit_to_bounds(circle_gfx, bounds));
    if (hitbox_static_objects)
      hitbox();
  }
};

class Banana{};
class Water{};

#endif //ECO_WORLD_OBJECTS_H
