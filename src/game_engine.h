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
  b2Body *wall_up;
  b2Body *wall_down;
  
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
    float r = 10;
    b2BodyDef center;
    b2PolygonShape rect;
    
    center.position.Set(edge_right + r, 0);
    rect.SetAsBox(r, edge_top);
    
    wall_right = world.CreateBody(&center);
    wall_right->CreateFixture(&rect, 0);
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
        blobs.emplace_back(x, y);
        for (int i = 1; i < count; i++)
        {
          int spread = count * 6;
          blobs.emplace_back(Ask::random(x - spread, x + spread), Ask::random(y - spread, y + spread));
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
};

#endif