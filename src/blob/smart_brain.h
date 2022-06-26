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
  float value = 0; /// mellom 0.0 og 1.0

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
    {
      i->fire();
    }
    
//    for (auto &i : output)
//      i->value = Ask::squeeze(i->value);
    
  }
  
  void render(sf::RenderTexture &texture)
  {
    texture.clear();
    static float r = 8;
    static sf::CircleShape c(r);
    c.setOrigin(c.getRadius(), c.getRadius());
    
//    int x1 = (texture.getSize().y + 2 * r) / (input.size() + 1);
//    int x2 = (texture.getSize().y + 2 * r) / (output.size() + 1);
    
    sf::Vector2f vec_in = {r * 2, (texture.getSize().y + 2 * r) / (input.size() + 1)};
    sf::Vector2f vec_out = {texture.getSize().x - r * 2, (texture.getSize().y + 2 * r) / (output.size() + 1)};
  
    for (int i = 0; i < input.size(); i++)
    {
      sf::Vector2f a = {vec_in.x, vec_in.y * (i + 1)};
      
      for (int j = 0; j < input[i]->outputs.size(); j++)
      {
        sf::Vector2f b = {vec_out.x, vec_out.y * (j + 1)};
        texture.draw(line
        (a, b,
         input[i]->outputs[j].strength * 4,
         {255, 240, 240, (sf::Uint8) (255 * input[i]->outputs[j].strength * input[i]->value)}));
      }
      c.setPosition(a);
      c.setFillColor({255, 255, 255, (sf::Uint8)(255 * input[i]->value)});
      texture.draw(c);
    }
    
    for (int i = 0; i < output.size(); i++)
    {
      sf::Vector2f pos = {vec_out.x, vec_out.y * (i + 1)};
      c.setPosition(pos);
      c.setFillColor({255, 255, 255, (sf::Uint8)(255 * output[i]->value)});
      texture.draw(c);
    }
    
    
    texture.draw(c);
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
    
    int reseptors = senses.reseptors.size();
    for (int i = 0; i < reseptors; i++)
      neural_network.input[i]->value = senses.reseptors[i];
    
    neural_network.input[reseptors]->value = senses.pulse;
    
    neural_network.calculate_output();
    a.speed = neural_network.output[0]->value;
    a.right_torque = neural_network.output[0]->value;
    a.left_torque = neural_network.output[2]->value;
    
    return a;
  }

public:
  sf::RenderTexture *neurons_graphic; // TODO vent med å lage texture til det er nødvendig

public:
  Smart_brain() : neural_network(4, 3)
  {
    // network
    
  
    // graphics
    neurons_graphic = new sf::RenderTexture(); // dynamic memory fordi std::vector klarer ikke å kopiere
    neurons_graphic->create(512, 512);
  }
  ~Smart_brain(){delete neurons_graphic;}
  
  const sf::RenderTexture &render()
  {
    neural_network.render(*neurons_graphic);
    return *neurons_graphic;
  }
  
private:
  Neural_network neural_network;
};

#endif //ECO_SMART_BRAIN_H
