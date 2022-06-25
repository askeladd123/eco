//
// Her er kun Neural Network til en skapning
//

#ifndef ECO_BRAIN_H
#define ECO_BRAIN_H

#include "ask/praktisk.h"
#include "common.h"

class Brain
{
public:
  virtual instructions think(const Senses &senses) = 0;
};

class Stupid_brain : public Brain
{
public:
  instructions think(const Senses &senses) override
  {
    instructions a;
    if (0.9999 < senses.pulse && senses.pulse < 1.f)
    {
      a.torque = Ask::random(0.f, 1.f);
      a.speed = Ask::random(0.f, 1.f);
    }
    return a;
  }
};

class Smart_brain : public Brain
{
public:
  instructions think(const Senses &senses) override
  {
    instructions a;
    return a;
  }

public:
  sf::RenderTexture *neurons_graphic;

public:
  Smart_brain()
  {
    neurons_graphic = new sf::RenderTexture(); // dynamic memory fordi std::vector klarer ikke å kopiere
    neurons_graphic->create(128, 128);
    neurons_graphic->clear();
    sf::CircleShape c;
    c.setRadius(4);
    neurons_graphic->draw(c);
  }
  ~Smart_brain(){delete neurons_graphic;}
};

#endif //ECO_BRAIN_H
