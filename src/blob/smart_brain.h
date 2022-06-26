//
// Created by askso on 25/06/2022.
//

#ifndef ECO_SMART_BRAIN_H
#define ECO_SMART_BRAIN_H

#include "SFML/Graphics.hpp"
#include "ask/praktisk.h"
#include "brain.h"

class Neuron;
struct Connection
{
  Neuron *neuron;
  float strength;
  Connection(Neuron *neuron, float strength) : neuron(neuron), strength(strength){}
};

class Neuron
{
public:
  float value = 0.5; /// mellom 0.0 og 1.0

private:
  void connect(Neuron *with_this)
  {
    outputs.emplace_back(with_this, Ask::random(0, 1));
  }

  void fire() /// aktiverer "barna" sine. Nå kan "value" bli over 1
  {
    for (auto &i: outputs)
    {
      i.neuron->value += value * i.strength;
    }
  }
  
private:
  std::vector<Connection> outputs;
//  bool is_root = false;
//  std::string name = "";

friend class Neural_network;
};

class Neural_network
{
public:
//  const int input_layer_size, output_layer_size, hidden_layers, hidden_layer_size;
  std::vector<Neuron*> input, output;
  std::vector<std::vector<Neuron*>> hiddens;

public:
  Neural_network(int input_layer_size, int output_layer_size, int hidden_layers = 0, int hidden_layer_size = 10)
//  input_layer_size(input_layer_size),
//  output_layer_size(output_layer_size),
//  hidden_layers(hidden_layers),
//  hidden_layer_size(hidden_layer_size)
  {
    int size = input_layer_size + output_layer_size + hidden_layer_size * hidden_layers;
    neurons = new Neuron[size];
    
    // alias i std::vector
    input.resize(input_layer_size);
    for (int i = 0; i < input_layer_size; i++)
      input[i] = neurons + i;
    
    output.resize(output_layer_size);
    for (int i = input_layer_size; i < input_layer_size + output_layer_size; i++)
      output[i] = neurons + i;
  
    output.resize(output_layer_size);
    for (int i = 0; i < output_layer_size; i++)
      output[i] = neurons + i + input_layer_size;
    
    // linke nervene
    for (auto &i : input)
      for (auto &j : output)
        i->connect(j);
  }
  
  ~Neural_network(){delete[] neurons;}
  
  void calculate_output()
  {
    for (auto &i : output)
      i->value = 0;
    
    for (auto &i : input)
      i->fire();
    
    // husk sigmoid
  }
  
private:
  Neuron *neurons;
};

class Smart_brain : public Brain
{
public:
  Instructions think(const Senses &senses) override
  {
    Instructions a;
    
    neural_network.input[0]->value = senses.pulse;
    neural_network.calculate_output();
    a.torque = neural_network.output[0]->value;
    a.speed = neural_network.output[1]->value;
    
    return a;
  }

public:
  sf::RenderTexture *neurons_graphic; // TODO vent med å lage texture til det er nødvendig

public:
  Smart_brain() : neural_network(1, 2)
  {
    // network
    
  
    // graphics
    neurons_graphic = new sf::RenderTexture(); // dynamic memory fordi std::vector klarer ikke å kopiere
    neurons_graphic->create(128, 128);
    neurons_graphic->clear();
    sf::CircleShape c;
    c.setRadius(4);
    neurons_graphic->draw(c);
  }
  ~Smart_brain(){delete neurons_graphic;}
  
private:
  Neural_network neural_network;
};

#endif //ECO_SMART_BRAIN_H
