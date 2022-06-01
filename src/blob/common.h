//
// Created by askso on 31/05/2022.
//

#ifndef ECO_COMMON_H
#define ECO_COMMON_H

#include "ask/praktisk.h"

struct instructions
{
  float rotation = 0, velocity = 0;
};

struct senses
{
  std::vector<float>* reseptors; float pulse;
};

struct genes_logic
{
  genes_logic()
  {
    pulse_speed = Ask::random(0.f, 2.f);
  }
  float pulse_speed = 1.f;
};

#endif //ECO_COMMON_H
