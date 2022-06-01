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
  float x, y, v_angle, v;
  
public:
  senses pull()
  {
    senses s;
    s.pulse = cos(ticks_since_startup * genes.pulse_speed);
    return s;
  }
  
  void push(instructions instructions)
  {
    v_angle += instructions.rotation;
    v = instructions.velocity;
  }
  
  float vx()
  {
    return v * cos(v_angle);
  }
  
  float vy()
  {
    return v * sin(v_angle);
  }

private:
  std::vector<float> reseptors;
  genes_logic genes;
};

#endif //ECO_LOGIC_H
