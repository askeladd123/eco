/*
 * brain, graphics og logic møtes her
 */
#ifndef ECO_BLOB_H
#define ECO_BLOB_H

#include "global_var.h"
#include "common.h"
#include "logic.h"
#include "brain.h"
#include "graphics.h"

/// binder alle komponentene i en blob sammen
class Blob
{
public:
  Logic logic;
  Stupid_brain brain;
  Graphics_circle graphics;
  
  /// justerer akselerasjon: må fortsatt legge til på fart og posisjon
  void think()
  {
    auto senses = logic.pull();
    
    auto instructions = brain.think(senses);
    
    logic.push(instructions);
  }
  
  void render()
  {
    graphics.render(logic);
  }
};

#endif
