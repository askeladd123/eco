//
// Ansvar for møte mellom skapninger og verden rundt
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
        blobs.emplace_back(Logic(), Brain(), Graphics());
        return {blobs.back().logic.x, blobs.back().logic.y};
    }
  }
  
  // flow
  void tick()
  {
    for (Blob &blob : blobs)
      blob.logic.tick();
  }
  
  void render(sf::RenderWindow& window)
  {
    for (Blob &blob : blobs)
      blob.graphics.render(window);
  }
  
private:
  std::vector<Blob> blobs;
};