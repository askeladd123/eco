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
  Ask::Physics::Vector<float> pos, vel;
//  float x, y, vx = 0, vy = 0;
  float a_len = 0;
  float a_angle;///< i radianer
  float mass = 1;
  bool intersected = false;
  
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
  std::vector<Ask::Physics::Ray> reseptors;
  genes_logic genes;
};

#endif //ECO_LOGIC_H
