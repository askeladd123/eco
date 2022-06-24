/*
 * Ansvar for fart og retning
 */

#ifndef ECO_LOGIC_H
#define ECO_LOGIC_H

#include "box2d/box2d.h"

#include "global_var.h"
#include "global_func.h"
#include "common.h"

class Ray : public b2RayCastCallback
{
public:
  b2Vec2 start = {0, 0}, /*intersection = {5, 5},*/ end = {10, 10};
  float angle = 0;
  float max_length = 4;
  float length = max_length;
  float intersection_fraction = 1;
  Entity *entitiy_hit;
//  bool intersected = false;
  
  void reset()
  {
//    intersected = false;
    length = max_length;
    intersection_fraction = 1;
  }
  
  #define float32 float
  float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override
  {
//    intersected = false;
    entitiy_hit = (Entity*)fixture->GetBody()->GetUserData().pointer;
//    intersection = point;
    intersection_fraction = fraction;
    return 0;
  }
};

class Logic : public Entity
{
public:
  b2Body *body;
  int r = 8;
  std::vector<Ray> rays;
  float rays_count = 16;
  float rays_length = 10;
  float rays_arc = M_PI;
  
//public:
//  Ask::Physics::Vector<float> pos, vel;
//  float x, y, vx = 0, vy = 0;
//  float a_len = 0;
//  float a_angle;///< i radianer
//  float mass = 1;
//  bool intersected = false;
  
public:
  Logic(int x, int y) : Entity(Entity::BLOB)
  {
    for (int i = 0; i < rays_count; i++)
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
    body->GetUserData().pointer = (uintptr_t)this;
  }
  /// Gir hjernen informasjon: husk at verdiene skal være 1, 0, eller mellom
  senses pull()
  {
    senses s;
  
    update_rays();
    for (Ray &ray : rays)
    {
      world.RayCast(&ray, ray.start, ray.end);
    }
    
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
  void update_rays()
  {
    b2Vec2 center = body->GetPosition();
    
    for (int i = 0; i < rays.size(); i++)
    {
      Ray &ray = rays[i];
      
      ray.reset();
      
      ray.angle = body->GetAngle() + i * rays_arc / rays.size();
      b2Vec2 u = {cos(ray.angle), sin(ray.angle)};
      
      float d = meters(r);
      ray.start = {center.x + u.x * d, center.y + u.y * d};
  
      ray.end.x = ray.start.x + u.x * ray.length,
      ray.end.y = ray.start.y + u.y * ray.length;
    }
  }
  
private:
  genes_logic genes;
};

#endif //ECO_LOGIC_H
