//
// Ansvar for møte mellom skapninger og verden rundt, fysikk
//

#include <vector>

#include "global_var.h"
#include "blob/blob.h"
#include "ask/collision.h"

class World
{
  // list static objects;
  // list moving objects;
  
  // TODO quad trees for collision
public:
  Ask::Physics::Box bounds;
  
public:
  
  
  // flow
  void tick()
  {
    for (Blob &blob : blobs)
    {
      blob.think();
      
      // physics og tick osv.
      blob.logic.x += blob.logic.vx();
      blob.logic.y += blob.logic.vy();
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