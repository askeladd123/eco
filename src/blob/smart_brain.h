//
// Created by askso on 25/06/2022.
//

#ifndef ECO_SMART_BRAIN_H
#define ECO_SMART_BRAIN_H

#include "SFML/Graphics.hpp"
#include "ask/matte.h"
#include "brain.h"
#include "neural_net.h"

class Smart_brain : public Brain
{
public:
  Instructions think(const Senses &senses) override
  {
    Instructions a;
    
    std::vector<float> values(senses.reseptors);
    values.push_back(senses.pulse);
    values.push_back(bias);
    neural_net.set_input(values);
    neural_net.calculate_output();
//
//    neural_net.input[reseptors]->value = senses.pulse;
//
//    neural_net.calculate_output();
    a.speed = neural_net.values.back()[0];
    a.right_torque = neural_net.values.back()[1];
    a.left_torque = neural_net.values.back()[2];
    
    return a;
  }

public:
  sf::RenderTexture *neurons_graphic; // TODO vent med å lage texture til det er nødvendig

public:
  Smart_brain() : neural_net(5, 3), bias(Ask::random(0.f, 1.f))
  {
    // network
    
  
    // graphics
    neurons_graphic = new sf::RenderTexture(); // dynamic memory fordi std::vector klarer ikke å kopiere
    neurons_graphic->create(512, 512);
  }
  ~Smart_brain(){delete neurons_graphic;}
  
  const sf::RenderTexture &render()
  {
    neural_net.render(*neurons_graphic);
    return *neurons_graphic;
  }
  
private:
  Neural_net neural_net;
  float bias;
};

#endif //ECO_SMART_BRAIN_H
