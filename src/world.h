//
// Ansvar for møte mellom skapninger og verden rundt, fysikk
//

#include <vector>

#include "ask/collision.h"
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
  float basically_zero = 0.001f;
  float friction_a = 0.02f;
  
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
      float &x_vel = blob.logic.vx;
      float &y_vel = blob.logic.vy;
      float &len_acc = blob.logic.a_len;
      float &angle_acc = blob.logic.a_angle;
      
      // interne krefter ================================
      x_vel += len_acc * cos(angle_acc);
      y_vel += len_acc * sin(angle_acc);
      
      // eksterne krefter ================================
      // TODO: collision
      
      // friksjon
      if (0 < x_vel)
        x_vel -= x_vel * friction_a;

      if (x_vel < 0)
        x_vel += x_vel * friction_a;

      if (0 < y_vel)
        y_vel -= y_vel * friction_a;

      if (y_vel < 0)
        y_vel += y_vel * friction_a;

      // stopp helt
      if (-basically_zero < x_vel && x_vel < basically_zero)
        x_vel = 0;

      if (-basically_zero < y_vel && y_vel < basically_zero)
        y_vel = 0;
      
      // collision
      if (intersects(Point(x, y), Box(400, 400, 400, 400)))
        blob.graphics.set_color(blob.graphics.RED);

      else
        blob.graphics.set_color(blob.graphics.WHITE);
      
      // posisjon ================================
      blob.logic.x += blob.logic.vx;
      blob.logic.y += blob.logic.vy;
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