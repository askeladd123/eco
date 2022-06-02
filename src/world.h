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
  World():bounds(0, 0, 800, 800){}
  
public:
  Ask::Physics::Box bounds;
  float basically_zero = 0.005f;
  float friction_c = 0.2f, drag_c = 0.05f;
  
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
      
      // collision
      for (auto &blob2: blobs)
        if (&blob2 != &blob && intersects(blob.graphics.bounds, blob2.graphics.bounds))
        {
          float normal_angle = (blob2.logic.v_angle - vel_angle) / 2 + M_PI / 2;
          vel_angle += normal_angle;
          blob2.logic.v_angle -= normal_angle;
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
    sf::RectangleShape rect({(float)bounds.w, (float)bounds.h});
    rect.setPosition({(float)bounds.x, (float)bounds.y});
    rect.setFillColor(sf::Color(30, 30, 30));
    window.draw(rect);
    for (Blob &blob : blobs)
      blob.render();
  }
  
  // setup
  enum item_id {BLOB};
  class response
  {
  public:
    response(float &x, float &y):x(&x), y(&y){}
    void and_move(int x, int y){*this->x = x; *this->y = y;}
  private:
    float *x, *y;
  };
  
  response add(item_id item_type)
  {
    switch(item_type)
    {
      case BLOB:
        blobs.emplace_back();
        return {blobs.back().logic.x, blobs.back().logic.y};
    }
  }
  
private:
  std::vector<Blob> blobs;
};