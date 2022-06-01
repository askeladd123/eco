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
    if (0 < senses.pulse && senses.pulse < 0.01)
      a.rotation = Ask::random(0.f, 10.f);
    a.velocity = 0.8f;
    return a;
  }
};

#endif //ECO_BRAIN_H
