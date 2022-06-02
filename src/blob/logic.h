/*
 * Ansvar for fart og retning
 */

#ifndef ECO_LOGIC_H
#define ECO_LOGIC_H

#include "global_var.h"
#include "common.h"

class Logic
{
public:
  float x, y, vx, vy, a_len, a_angle;
  
public:
  senses pull()
  {
    senses s;
    s.pulse = cos(ticks_since_startup * genes.pulse_speed);
    return s;
  }
  
  void push(instructions instructions)
  {
    a_angle += instructions.rotation;
    a_len = instructions.velocity;
  }

private:
  std::vector<float> reseptors;
  genes_logic genes;
};

#endif //ECO_LOGIC_H
