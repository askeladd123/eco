/*
 * Ansvar for fart og retning
 */

#ifndef ECO_LOGIC_H
#define ECO_LOGIC_H

#include "box2d/box2d.h"

#include "global_var.h"
#include "common.h"

class Ray : public b2RayCastCallback
{
public:
  b2Vec2 source;
  float angle;
  float length_result;
  
  #define float32 float
  float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override
  {
    length_result *= fraction;
    return 0;
  }
};

class Logic
{
public:
  b2Body *body;
  int r = 8;
  std::vector<Ray> rays;
  float ray_length = 10;
  
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
    rays.emplace_back();
    
    // box2d
    b2BodyDef b;
    b.type = b2_dynamicBody;
    b.position.Set(meters(x), meters(y));
    body = world.CreateBody(&b);
    
    b2CircleShape circle;
    circle.m_radius = meters(r);
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
//    for (Ray ray : rays)
//    {
//      world.RayCast(&ray, body->GetPosition(), {0, 10});
//    }
      align_rays();
      Ray &ray = rays[0];
      world.RayCast(&ray, ray.source, {ray_length * cos(ray.angle), ray_length * sin(ray.angle)});

    s.pulse = 0.5f + cos(ticks_since_startup * genes.pulse_speed) / 2.f;
    return s;
  }
  
  /// Tar imot kommandoer fra hjernen: husk at instruksjons-verdiene er 1, 0, eller mellom
  void push(instructions instructions)
  {
    body->ApplyTorque(instructions.force_angle/100, true);
    
    float strength = instructions.force_len * genes.max_accel;
    body->ApplyForceToCenter({cos(body->GetAngle()) * strength, sin(body->GetAngle()) * strength}, true);
  }

private:
  void align_rays()
  {
    rays[0].length_result = ray_length;
    rays[0].source = body->GetPosition();
    rays[0].angle = body->GetAngle();
  }
  
private:
  genes_logic genes;
};

#endif //ECO_LOGIC_H
