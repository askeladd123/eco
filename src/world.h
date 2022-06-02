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
      for (auto &bro: blobs)
        if (&bro != &blob && intersects(blob.graphics.bounds, bro.graphics.bounds))
        {
          blob.graphics.set_color(blob.graphics.RED);
          break;
        }
        else
          blob.graphics.set_color(blob.graphics.WHITE);
      
      // posisjon ================================
      x += vel_len * cos(vel_angle);
      y += vel_len * sin(vel_angle);
    }
  }
  
  void render()
  {
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