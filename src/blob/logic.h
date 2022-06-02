/*
 * Ansvar for fart og retning
 */

#ifndef ECO_LOGIC_H
#define ECO_LOGIC_H

#include "global_var.h"
#include "common.h"

class Logic
{
public:
  float x, y, v_len = 5.f, a_len;
  float v_angle = 0.4, a_angle;  ///< i radianer
  
public:
  /// Gir hjernen informasjon: husk at verdiene skal være 1, 0, eller mellom
  senses pull()
  {
    senses s;
    s.pulse = 0.5f + cos(ticks_since_startup * genes.pulse_speed) / 2.f;
    return s;
  }
  
  /// Tar imot kommandoer fra hjernen: husk at instruksjons-verdiene er 1, 0, eller mellom
  void push(instructions instructions)
  {
    a_angle = instructions.force_angle * 2.f * M_PI;
    a_len = instructions.force_len * genes.max_accel;
  }

private:
  std::vector<float> reseptors;
  genes_logic genes;
};

#endif //ECO_LOGIC_H
