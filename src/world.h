//
// Ansvar for møte mellom skapninger og verden rundt, fysikk
//

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "blob/blob.h"

class world
{
  // list static objects;
  // list moving objects;
  
  // TODO quad trees for collision
  
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
  
  void render(sf::RenderWindow& window)
  {
    for (Blob &blob : blobs)
      blob.render(window);
  }
  
  // setup
  enum item_id {BLOB};
  class response
  {
  public:
    response(int &x, int &y):x(&x), y(&y){}
    void and_move(int x, int y){*this->x = x; *this->y = y;}
  private:
    int *x, *y;
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