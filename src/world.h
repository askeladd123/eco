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
  float max_vel = 1;
  float basically_zero = 0.1f;
  float friction_a = 0.002f;
  
public:
  // flow
  void tick()
  {
    for (Blob &blob : blobs)
    {
      blob.think();
      
      // physics og tick osv.
      float &x = blob.logic.x;
      float &y = blob.logic.y;
      float &x_vel = blob.logic.vx;
      float &y_vel = blob.logic.vy;
      float &len_acc = blob.logic.a_len;
      float &angle_acc = blob.logic.a_angle;
      
      // interne krefter
      if (x_vel < max_vel)
        x_vel += len_acc * cos(angle_acc);
      
      if (y_vel < max_vel)
        y_vel += len_acc * sin(angle_acc);
      
      // eksterne krefter
      // TODO: collision
      if (0 < x_vel)
        x_vel *= -friction_a;
      
      if (x_vel < 0)
        x_vel *= friction_a;
      
      if (-basically_zero < x_vel && x_vel < basically_zero)
        x_vel = 0;
  
      if (-basically_zero < y_vel && y_vel < basically_zero)
        y_vel = 0;
  
  
      using namespace Ask::Physics;
      
      if (intersects(Point(x, y), Box(400, 400, 400, 400)))
        blob.graphics.set_color(blob.graphics.RED);

      else
        blob.graphics.set_color(blob.graphics.WHITE);
      
      // posisjon
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