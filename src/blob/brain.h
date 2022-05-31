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
    a.rotation = 3;
    a.velocity = 8;
    return a;
  }
};

#endif //ECO_BRAIN_H
