//
// Her er kun Neural Network til en skapning
//

#ifndef ECO_BRAIN_H
#define ECO_BRAIN_H

#include "common.h"

class Brain
{
public:
  instructions think(senses senses)
  {
    instructions a;
    a.rotation = 0.8;
    a.velocity = 0.6;
    return a;
  }
};

#endif //ECO_BRAIN_H
