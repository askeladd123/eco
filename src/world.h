//
// Ansvar for møte mellom skapninger og verden rundt, fysikk
//

#include <vector>

#include "ask/physics.h"
#include "global_var.h"
#include "blob/blob.h"

class World
{
  // list static objects;
  // list moving objects;
  
  // TODO quad trees for collision
public:
  World():bounds(0, 0, 800, 800)
  {
    point.setRadius(2);
    point.setOrigin({point.getRadius(), point.getRadius()});
    background.setFillColor(sf::Color(30, 30, 30));
  }
  
public:
  std::vector<Blob> blobs;
  Ask::Physics::Box bounds;
  float basically_zero = 0.005f;
  float friction_c = 0.2f, drag_c = 0.05f;
  sf::CircleShape point;
  sf::RectangleShape background;
  
public:
  // flow
  void tick()
  {
    for (Blob &blob : blobs)
    {
      using namespace Ask::Physics;
  
      blob.think();
      
      // alias for variabler
      float &x = blob.logic.x;
      float &y = blob.logic.y;
      float &vel_len = blob.logic.v_len;
      float &vel_angle = blob.logic.v_angle;
      float &acc_len = blob.logic.a_len;
      float &acc_angle = blob.logic.a_angle;
      
      // interne krefter ================================
      vel_len += acc_len;
      vel_angle += acc_angle;
      
      // eksterne krefter ================================
      // TODO: collision
      
      // friksjon
      if (vel_len < basically_zero)
        vel_len = 0;

      // TODO: vurdere om drag er unødvendig
      vel_len -= vel_len * friction_c;
      
      bool crash = false;
      // collision
      for (auto &blob2: blobs)
      {
        if (&blob2 == &blob)
          continue;
        
        // kollisjon sirkel sirkel
        auto a = blob.graphics.bounds;
        auto b = blob2.graphics.bounds;
        int x1 = b.x - a.x;
        int y1 = b.y - a.y;
        float distance_between = sqrt(x1 * x1 + y1 * y1) - (b.r + a.r);
        if (distance_between < 0)
        {
          crash = true;
  
          // ikke lov å være inni hverandre
//          float between_x = (blob2.logic.x - x) / 2;
//          float between_y = (blob2.logic.y - y) / 2;

//          x -= between_x;
//          y -= between_y;
//          blob2.logic.x += between_x;
//          blob2.logic.y += between_y;

//          point.setPosition({x + between_x, y + between_y});

          // ikke lov å være inni hverandre: polar løsning. TODO: finn en cartesisk løsning bro
//          float angle_between = atan2(blob2.logic.x - x, blob2.logic.y - y);
//          float h = distance_between / 2;
//          float new_x = h * cos(angle_between) + 1;
//          float new_y = h * sin(angle_between) + 1;
//          x += new_x;
//          y += new_y;
//          blob2.logic.x -= new_x;
//          blob2.logic.y -= new_y;
//
//
          float between_x = (blob2.logic.x - x) / 2;
          float between_y = (blob2.logic.y - y) / 2;
          
          
          
          // reflekt
          float normal_angle = (blob2.logic.v_angle - vel_angle) / 2 + M_PI / 2;
          vel_angle += normal_angle;
          blob2.logic.v_angle -= normal_angle;
        }
      }
  
      if (hitbox_blob)
      {
        if (crash)
          blob.graphics.bounds_gfx.setFillColor(hitbox_hit);
        else
          blob.graphics.bounds_gfx.setFillColor(hitbox_unhit);
      }
      
      float vel_x = vel_len * cos(vel_angle);
      float vel_y = vel_len * sin(vel_angle);
      
      // collision world bounds
      if (x < bounds.x)
      {
        x = bounds.x;
        vel_x += vel_len;
      }
  
      if (bounds.x + bounds.w < x)
      {
        x = bounds.x + bounds.w;
        vel_x -= vel_len;
      }
      
      if (y < bounds.y)
      {
        y = bounds.y;
        vel_y += vel_len;
      }
  
      if (bounds.y + bounds.h < y)
      {
        y = bounds.y + bounds.h;
        vel_y -= vel_len;
      }
      
      // posisjon ================================
      x += vel_x;
      y += vel_y;
    }
  }
  
  void render()
  {
    window.draw(fit_to_bounds(background, bounds));
    for (Blob &blob : blobs)
      blob.render();
//    window.draw(point);
  }
  
  // setup
  enum item_id {BLOB};
  void add(item_id item_type, int x, int y, int count = 1)
  {
    switch(item_type)
    {
      case BLOB:
        blobs.emplace_back();
        auto &a = blobs.back();
        a.logic.x = x;
        a.logic.y = y;
        for (int i = 1; i < count; i++)
        {
          blobs.emplace_back();
          auto &b = blobs.back();
          int spread = count * 6;
          b.logic.x = Ask::random(x - spread, x + spread);
          b.logic.y = Ask::random(y - spread, y + spread);
        }
    }
  }
};