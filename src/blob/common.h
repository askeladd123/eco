//
// Created by askso on 31/05/2022.
//

#ifndef ECO_COMMON_H
#define ECO_COMMON_H

#include "ask/praktisk.h"

/// Alle verdier skal være 0, 1 eller mellom
struct Instructions
{
  float torque = 0.f;
  float speed = 0.f;
};

/// Alle verdier skal være 0, 1 eller mellom
struct Senses
{
  std::vector<float> reseptors;
  float pulse;
  float angle;
  
  Senses(int reseptor_count)
  {
//    reseptors.reserve(reseptor_count);
    reseptors.resize(reseptor_count);
    reseptors.shrink_to_fit();
  }
};

/// Alle verdier skal være 0, 1 eller mellom
struct Genes_logic
{
  Genes_logic()
  {
    pulse_speed = Ask::random(0.1f, 10.f);
    max_accel = Ask::random(0.1f, 6.f);
  }
  float pulse_speed = 1.f;
  float max_accel = 6.f;
  
};


#endif //ECO_COMMON_H
