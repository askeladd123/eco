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
  virtual instructions think(senses senses) = 0;
};

class Stupid_brain : public Brain
{
public:
  instructions think(senses senses) override
  {
    instructions a;
    if (0.97 < senses.pulse && senses.pulse < 1.f)
    {
      a.force_angle = Ask::random(0.f, 1.f);
      a.force_len = Ask::random(0.f, 1.f);
    }
    return a;
  }
};

#endif //ECO_BRAIN_H
