//
// Ansvar for møte mellom skapninger og verden rundt, fysikk
//

#include <cmath>
#include <vector>
#include <string>

#include "ask/physics.h"
#include "global_var.h"
#include "blob/blob.h"
#include "world_objects.h"

class World
{
  // list static objects;
  // list moving objects;
  
  // TODO quad trees for collision
public:
  std::vector<Blob> blobs;
  std::vector<Static_object*> obstacles;
  std::vector<Banana> bananas;
  std::vector<Water> water;
  Ask::Physics::Tile bounds;
  float basically_zero = 0.f;
  float friction_c = 0.2f, drag_c = 0.05f;
  
  //graphics
  sf::CircleShape point;
  sf::RectangleShape background, overlay;

public:
  World():bounds(0, 0, 400, 400)
  {
    point.setRadius(2);
    point.setOrigin({point.getRadius(), point.getRadius()});
    background.setTexture(&files.tiles);
    background.setTextureRect({0, 0, 1600, 1600});
    overlay.setTexture(&files.concrete);
    overlay.setTextureRect({0, 0, 2000, 2000});
  }
  
public:
  // flow
  void tick()
  {
    using namespace Ask::Physics;
  
    // TODO: unngå polar conversion
  
    // OPPDATER POSISJON
    for (Blob &i: blobs)
    {
      // bra navn
      // logic inneholder fysikkting
      Logic &blob = i.logic;
    
      // akselerasjon
      i.think();
      blob.vel.x += blob.a_len * cos(blob.a_angle);
      blob.vel.y += blob.a_len * sin(blob.a_angle);
      
      if (basically_zero < sqrt(blob.vel.x * blob.vel.x + blob.vel.y * blob.vel.y))
      {
        // friksjon
        blob.vel.x -= blob.vel.x * friction_c;
        blob.vel.y -= blob.vel.y * friction_c;
  
        // fart
        blob.pos += blob.vel;
      }
    }
    
    /* CORRECTION & DEFLECTION
     * TODO: threadpool
     */
    for (Blob &i: blobs)
    {
      Logic &blob = i.logic;
    
      for (const Blob &j: blobs)
      {
        // bra navn
        const Logic &blob2 = j.logic; // const pga. thread safety
      
        auto collision = intersection_c(i.graphics.bounds, j.graphics.bounds);
        blob.intersected |= collision.intersects;
      
        if (collision.intersects)
          // bounds ligger i graphics istedenfor logic
          // - er jo knyttet til utseende
        {
          // CORRECTION
          blob.pos -= blob.vel;
        
          // DEFLECTION
//          Vector<float> proj = collision.collision_unit_normal *
//                               (collision.collision_unit_normal * blob.vel);//virker bare hvis CN er enhetsV
//          blob.vel -= proj * 2;
        }
      }
    
      // CORRECTION med world.bounds
//      if (blob.pos.x < bounds.center.x - bounds.r_x)
//      {
//        blob.pos.x = bounds.center.x - bounds.r_x;
//        blob.vel.x += 3;
//      }
//
//      if (bounds.center.x + bounds.r_x < blob.pos.x)
//      {
//        blob.pos.x = bounds.center.x + bounds.r_x;
//        blob.vel.x -= 3;
//      }
//
//      if (blob.pos.y < bounds.center.y - bounds.r_y)
//      {
//        blob.pos.y = bounds.center.y - bounds.r_y;
//        blob.vel.y += 3;
//      }
//
//      if (bounds.center.y + bounds.r_y < blob.pos.y)
//      {
//        blob.pos.y = bounds.center.y + bounds.r_y;
//        blob.vel.y -= 3;
//      }
    }
  }
  // GAMMEL GAMMEL GAMMEL GAMMEL GAMMEL GAMMEL GAMMEL GAMMEL
//    for (Blob &blob : blobs)
//    {
//      blob.think();
//      // alias for variabler
//      float &x = blob.logic.x;
//      float &y = blob.logic.y;
//      float &vel_len = blob.logic.v_len;
//      float &vel_angle = blob.logic.v_angle;
//      float &acc_len = blob.logic.a_len;
//      float &acc_angle = blob.logic.a_angle;
//
//      // interne krefter ================================
//      vel_len += acc_len;
//      vel_angle += acc_angle;
//
//      // friksjon
//      if (vel_len < basically_zero)
//        vel_len = 0;
//      vel_len -= vel_len * friction_c;
//
//      // collision ================================
//      for (auto &blob2: blobs)
//      {
//        if (&blob2 == &blob)
//          continue;
//
//        // kollisjon sirkel sirkel
//        auto collision = intersection_c(blob.graphics.bounds, blob2.graphics.bounds);
//        blob.logic.intersected = collision.intersects; // for å vise hitboxes
//
//        /*
//         * move (pos + vel)
//         * collision ---
//         * correction (pos)
//         * deflection (vel)
//         */
//
//        if (collision.intersects)
//        {
//          // correct
//          float a_len = collision.distance_inside / 2;
//          x -= a_len * collision.collision_unit_normal.x;
//          y -= a_len * collision.collision_unit_normal.y;
//          blob2.logic.x += a_len * collision.collision_unit_normal.x;
//          blob2.logic.y += a_len * collision.collision_unit_normal.y;
//
//          // reflekt
//          float normal_angle = (blob2.logic.v_angle - vel_angle) / 2 + M_PI / 2;
//          vel_angle += normal_angle;
//          blob2.logic.v_angle -= normal_angle;
//        }
//      }
//
//      float vel_x = vel_len * cos(vel_angle);
//      float vel_y = vel_len * sin(vel_angle);
//
//      for (auto &obj: obstacles)
//      {
//        auto collision = intersection_c(blob.graphics.bounds, obj->getBounds());
//        blob.logic.intersected |= collision.intersects;
//
//        if (collision.intersects)
//        {
//          // correct
//          x -= collision.distance_inside * collision.collision_unit_normal.x;
//          y -= collision.distance_inside * collision.collision_unit_normal.y;
//
//          vel_x -= vel_len * collision.collision_unit_normal.x;
//          vel_y -= vel_len * collision.collision_unit_normal.y;
//        }
//      }
//
//      // collision world bounds
//      if (x < bounds.center.x - bounds.r_x)
//      {
//        x = bounds.center.x - bounds.r_x;
//        vel_x += vel_len;
//      }
//
//      if (bounds.center.x + bounds.r_x < x)
//      {
//        x = bounds.center.x + bounds.r_x;
//        vel_x -= vel_len;
//      }
//
//      if (y < bounds.center.y - bounds.r_y)
//      {
//        y = bounds.center.y - bounds.r_y;
//        vel_y += vel_len;
//      }
//
//      if (bounds.center.y + bounds.r_y < y)
//      {
//        y = bounds.center.y + bounds.r_y;
//        vel_y -= vel_len;
//      }
//
//      // posisjon ================================
//      x += vel_x;
//      y += vel_y;
//  }
  
  void render()
  {
    // bakgrunn
    window.draw(fit_to_bounds(background, bounds));
    window.draw(fit_to_bounds(overlay, bounds));
    
    // folk
    for (Blob &blob : blobs)
      blob.render();
    
    for (auto &i : obstacles)
      i->render();
//    window.draw(point);
  }
  
  // setup
  enum item_id {NONE, BLOB, MELON, STICK};
  void add(int item_type, int x, int y, int count = 1)
  {
    switch(item_type)
    {
      case BLOB:
      {
        blobs.emplace_back();
        auto &a = blobs.back();
        a.logic.pos.x = x;
        a.logic.pos.y = y;
  
        for (int i = 1; i < count; i++)
        {
          blobs.emplace_back();
          auto &b = blobs.back();
          int spread = count * 6;
          b.logic.pos.x = Ask::random(x - spread, x + spread);
          b.logic.pos.y = Ask::random(y - spread, y + spread);
        }
      } break;
      case MELON:
        obstacles.push_back(new Melon(x, y, 20));
        break;
      
      case STICK:
        obstacles.push_back(new Stick(x, y, x + 100, y + 100));
        break;

      default: Ask::stop("World::add: object type not implemented");
    }
  }
};