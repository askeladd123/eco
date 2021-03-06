/*
 * brain, graphics og logic møtes her
 */
#ifndef ECO_BLOB_H
#define ECO_BLOB_H

#include "global_var.h"
#include "common.h"
#include "logic.h"
#include "brain.h"
#include "smart_brain.h"
#include "graphics.h"


/// binder alle komponentene i en blob sammen
class Blob
{
public:
  Logic logic;
  Smart_brain brain;
  Graphics_image graphics;
  std::string name;
  bool mute = false;
  
public:
  Blob(int x, int y) : logic(x, y), name(files.random_name()){}
  
  /// justerer akselerasjon: må fortsatt legge til på fart og posisjon
  void think()
  {
    
    const Senses &s = logic.pull();
    
    auto instructions = brain.think(s);
  
    if (mute) return;
    
    logic.push(instructions);
  }
  
  void render()
  {
    graphics.render(logic);
  }
};

#endif
