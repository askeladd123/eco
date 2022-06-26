//
// Her er kun Neural Network til en skapning
//

#ifndef ECO_BRAIN_H
#define ECO_BRAIN_H

#include "ask/praktisk.h"
#include "common.h"

class Brain
{
public:
  virtual Instructions think(const Senses &senses) = 0;
};

class Stupid_brain : public Brain
{
public:
  Instructions think(const Senses &senses) override
  {
    Instructions a;
    if (0.9999 < senses.pulse && senses.pulse < 1.f)
    {
      a.torque = Ask::random(0.f, 1.f);
      a.speed = Ask::random(0.f, 1.f);
    }
    return a;
  }
};



#endif //ECO_BRAIN_H
