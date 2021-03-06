/*
 * Ansvar for fart og retning
 */

#ifndef ECO_LOGIC_H
#define ECO_LOGIC_H

#include "box2d/box2d.h"

#include "global_var.h"
#include "global_func.h"
#include "common.h"

class Logic : public Entity
{
private:
  class Ray;
  friend class Graphics_image;
  
public:
  b2Body *body;
  int r = 8;
  std::vector<Ray> rays;
  float rays_count = 3;
  float rays_length = 10;
  float rays_arc = M_PI;
  Senses senses;
  
public:
  Logic(int x, int y) : Entity(Entity::BLOB), senses(rays_count)
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
    fixture.density = 10.f;
    fixture.friction = 1.f;
    body->CreateFixture(&fixture);
    body->GetUserData().pointer = (uintptr_t) this;
  }
  
  /// Gir hjernen informasjon: husk at verdiene skal være 1, 0, eller mellom
  const Senses &pull()
  {
    assert(rays.size() == senses.reseptors.size());
    
    for (int i = 0; i < rays.size(); i++)
      senses.reseptors[i] = 1.f - rays[i].intersection_fraction;
    
    update_rays();
    for (Ray &ray : rays)
      world.RayCast(&ray, ray.start, ray.end); // raycasten skjer ikke her, men i step
    
    senses.pulse = 0.5f + cos(ticks_since_startup * genes.pulse_speed) / 2.f;
    return senses;
  }
  
  /// Tar imot kommandoer fra hjernen: husk at instruksjons-verdiene er 1, 0, eller mellom
  void push(Instructions &instructions)
  {
    float vel = body->GetAngularVelocity();
    float friction = 0.5 * friction_c_r * vel * vel;
    float right = instructions.right_torque * genes.max_torque;
    float left = instructions.left_torque * genes.max_torque;
    body->ApplyAngularImpulse(right - left - friction, true);
    
    vel = body->GetLinearVelocity().Length();
    friction = 0.5 * friction_c * vel * vel;
    float strength = instructions.speed * genes.max_accel - friction;
    body->ApplyLinearImpulseToCenter({cos(body->GetAngle()) * strength, sin(body->GetAngle()) * strength}, true);
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
  Genes_logic genes;
  
private:
  class Ray : public b2RayCastCallback
  {
  public:
    b2Vec2 start = {0, 0}, end = {10, 10};
    Entity *entity_hit;
    float angle = 0;
    float max_length = 4;
    float length = max_length;
    float intersection_fraction = 1;
    
    typedef float float32;
    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override
    {
      entity_hit = (Entity *) fixture->GetUserData().pointer;
      intersection_fraction = fraction;
      return fraction;
    }
  
    void reset()
    {
      length = max_length;
      intersection_fraction = 1;
    }
  };
};

#endif //ECO_LOGIC_H
