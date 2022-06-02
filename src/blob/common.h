//
// Created by askso on 31/05/2022.
//

#ifndef ECO_COMMON_H
#define ECO_COMMON_H

#include "ask/praktisk.h"

/// Alle verdier skal være 0, 1 eller mellom
struct instructions
{
  float force_angle = 0.f;
  float force_len = 0.f;
};

/// Alle verdier skal være 0, 1 eller mellom
struct senses
{
  std::vector<float>* reseptors;
  float pulse;
  float angle;
};

/// Alle verdier skal være 0, 1 eller mellom
struct genes_logic
{
  genes_logic()
  {
    pulse_speed = Ask::random(0.f, 2.f);
    max_accel = Ask::random(1.f, 10.f);
  }
  float pulse_speed = 1.f;
  float max_accel = 6.f;
  
};

#endif //ECO_COMMON_H
