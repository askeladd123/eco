#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

//
// Ansvar for møte mellom skapninger og verden rundt, fysikk
//

#include <cmath>
#include <vector>
#include <string>

#include "box2d/box2d.h"

#include "global_var.h"
#include "blob/blob.h"
#include "world_objects.h"

class Game_engine
{
public:
  b2Body *wall_right;
  b2Body *wall_left;
  b2Body *wall_top;
  b2Body *wall_bottom;
  
  float timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;
  
  int edge_right = world_width / 2;
  int edge_left = -world_width / 2;
  int edge_top = edge_left;
  int edge_bottom = edge_right;
  
//public:
  std::vector<Blob> blobs;
//  std::vector<Static_object*> obstacles;
//  std::vector<Banana> bananas;
//  std::vector<Water> water;
//  Ask::Physics::Tile bounds;
//  float basically_zero = 0.f, activate_deflection_at = 1.f;
//  float friction_c = 0.2f, drag_c = 0.05f;
//
//  //graphics
//  sf::CircleShape point;
  sf::RectangleShape background, overlay;

public:
  Game_engine()
  {
    // graphics
    background.setTexture(&files.tiles);
    background.setTextureRect({0, 0, 1600, 1600});
    background.setPosition((float)edge_left, (float)edge_top);
    background.setSize({(float)world_width, (float)world_width});
    overlay.setTexture(&files.concrete);
    overlay.setTextureRect({0, 0, 2000, 2000});
    overlay.setPosition(background.getPosition());
    overlay.setSize(background.getSize());
    
    // world bounds
    float r = 100;
    b2BodyDef center;
    b2PolygonShape rect;
    
    center.position.Set(meters(edge_right + r), 0);
    rect.SetAsBox(meters(r), meters(edge_bottom + r * 2));
    wall_right = world.CreateBody(&center);
    wall_right->CreateFixture(&rect, 0);
  
    center.position.Set(meters(edge_left - r), 0);
    rect.SetAsBox(meters(r), meters(edge_bottom + r * 2));
    wall_left = world.CreateBody(&center);
    wall_left->CreateFixture(&rect, 0);
  
    center.position.Set(0, meters(edge_top - r));
    rect.SetAsBox(meters(edge_right + r * 2), meters(r));
    wall_top = world.CreateBody(&center);
    wall_top->CreateFixture(&rect, 0);
  
    center.position.Set(0, meters(edge_bottom + r));
    rect.SetAsBox(meters(edge_right + r * 2), meters(r));
    wall_top = world.CreateBody(&center);
    wall_top->CreateFixture(&rect, 0);
  }
  
public:
  // flow
  void tick()
  {
    ticks_since_startup++;
    
    for (Blob &blob : blobs)
    {
      blob.think();
    }
    
    world.Step(timeStep, velocityIterations, positionIterations);
  }
  
  void render()
  {
    // bakgrunn
    window.draw(background);
    window.draw(overlay);
    
    // folk
    for (Blob &blob : blobs)
      blob.render();
//
//    for (auto &i : obstacles)
//      i->render();
  }
  
  // setup
  enum item_id {NONE, BLOB, MELON, STICK, RAY};
  void add(int item_type, int x, int y, int count = 1)
  {
    switch(item_type)
    {
      case BLOB:
      {
        x = x < edge_left? edge_left : x;
        x = x > edge_right? edge_right : x;
        y = y < edge_top? edge_top : y;
        y = y > edge_bottom? edge_bottom : y;
        
        blobs.emplace_back(x, y);
        for (int i = 1; i < count; i++)
        {
          
          int spread = pow(count, 0.5) + count * 1.8;
          
          int xx = Ask::random(x - spread, x + spread);
          int yy = Ask::random(y - spread, y + spread);
  
          xx = xx < edge_left? edge_left : xx;
          xx = xx > edge_right? edge_right : xx;
          yy = yy < edge_top? edge_top : yy;
          yy = yy > edge_bottom? edge_bottom : yy;
          
          blobs.emplace_back(xx, yy);
        }
      } break;
//      case MELON:
//        obstacles.push_back(new Melon(x, y, 20));
//        break;
//
//      case STICK:
//        obstacles.push_back(new Stick(x, y, x + 100, y + 100));
//        break;
//
//      case RAY:
//        obstacles.push_back(new Ray(x, y, 100, 100));
//        break;
//
//      default: Ask::stop("Game_engine::add: object type not implemented");
    }
  }
  
  struct query_response : public b2QueryCallback
  {
    Entity *entity;
    bool collision = false;
    bool 	ReportFixture (b2Fixture *fixture) override
    {
      collision = true;
      entity = (Entity*)fixture->GetBody()->GetUserData().pointer;
      return false;
    }
  };
  
  /**
   * @return true: is entity at x, y - "result" changed
   * @return false: isn't entity at x, y - "result" unchanged
   */
  Entity *get_entity(int x, int y)
  {
    b2AABB m;
    float r = 0.1;
    m.lowerBound = {meters(mouse.x - r), meters(mouse.y - r)};
    m.upperBound = {meters(mouse.x + r), meters(mouse.y + r)};
    
    query_response qr;
    qr.entity = nullptr;
    world.QueryAABB(&qr, m);
    world.Step(timeStep, velocityIterations, positionIterations);
    return qr.entity;
  }
  
  struct entities{};
  entities get_entities_in(){}
};

#endif