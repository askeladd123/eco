//
// Created by askso on 31/05/2022.
//

#ifndef ECO_COMMON_H
#define ECO_COMMON_H

#include "ask/praktisk.h"

/// Alle verdier skal være 0, 1 eller mellom
struct Instructions
{
  float left_torque = 0.f, right_torque = 0.f, speed = 0.f;
};

/// Alle verdier skal være 0, 1 eller mellom
struct Senses
{
  std::vector<float> reseptors;
  float pulse, speed, angle;
  
  Senses(int reseptor_count)
  {
    reseptors.resize(reseptor_count);
    reseptors.shrink_to_fit();
  }
};

/// Alle verdier skal være 0, 1 eller mellom
struct Genes_logic
{
  float pulse_speed; ///lavere er tregere
  float max_accel, max_torque;
  
  Genes_logic()
  {
    pulse_speed = Ask::random(0.1f, 2.f);
    max_accel = Ask::random(0.1f, 6.f);
    max_torque = Ask::random(0.1f, 0.6f);
  }
  
};


#endif //ECO_COMMON_H
