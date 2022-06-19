/*
 * Ansvar for fart og retning
 */

#ifndef ECO_LOGIC_H
#define ECO_LOGIC_H

#include "box2d/box2d.h"

#include "global_var.h"
#include "common.h"

class Logic
{
public:
  b2Body *body;
  
//public:
//  Ask::Physics::Vector<float> pos, vel;
//  float x, y, vx = 0, vy = 0;
//  float a_len = 0;
//  float a_angle;///< i radianer
//  float mass = 1;
//  bool intersected = false;
  
public:
  Logic(int x, int y)
  {
    // box2d
    b2BodyDef b;
    b.type = b2_dynamicBody;
    b.position.Set(x, y);
    body = world.CreateBody(&b);
    
    b2CircleShape circle;
    circle.m_radius = 10.f;
    b2FixtureDef fixture;
    fixture.shape = &circle;
    fixture.density = 1.f;
    fixture.friction = 0.3f;
    
    body->CreateFixture(&fixture);
  }
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
    body->ApplyTorque(instructions.force_angle * 100000, true);
    
    float strength = instructions.force_len * genes.max_accel * 100000;
    body->ApplyForceToCenter({cos(body->GetAngle()) * strength, sin(body->GetAngle()) * strength}, true);
  }

private:
//  std::vector<Ask::Physics::Ray> reseptors;
  genes_logic genes;
};

#endif //ECO_LOGIC_H
