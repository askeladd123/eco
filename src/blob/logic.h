//
// ansvar for logikken til en skapning, bortsett fra NN
//

#ifndef ECO_LOGIC_H
#define ECO_LOGIC_H

#include "common.h"

class Logic
{
public:
  int x, y, v_angle, v;
  
public:
  senses pull()
  {
    return {};
  }
  
  void push(instructions instructions)
  {
    v_angle += instructions.rotation;
    v = instructions.velocity;
  }
  
  int vx()
  {
    return v * cos(v_angle);
  }
  
  int vy()
  {
    return v * sin(v_angle);
  }

private:
  std::vector<float> reseptors;
};

#endif //ECO_LOGIC_H
