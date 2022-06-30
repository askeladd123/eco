//
// Created by askso on 25/06/2022.
//

#ifndef ECO_SMART_BRAIN_H
#define ECO_SMART_BRAIN_H

#include "SFML/Graphics.hpp"
#include "ask/matte.h"
#include "brain.h"

class Neural_net
{
  typedef std::vector<std::vector<float>> matrix2d_float;
  typedef std::vector<std::vector<std::vector<float>>> matrix3d_float;
  
public:
//  const int input_layer_size, output_layer_size, hidden_layers, hidden_layer_size;
  matrix2d_float values;
  matrix3d_float weights;

public:
  Neural_net(int input_layer_size, int output_layer_size, int hidden_layers = 0, int hidden_layer_size = 10)
//  input_layer_size(input_layer_size),
//  output_layer_size(output_layer_size),
//  hidden_layers(hidden_layers),
//  hidden_layer_size(hidden_layer_size)
  {
//    int size = input_layer_size + output_layer_size + hidden_layer_size * hidden_layers;
//    neurons = new Neuron[size];
    
    int all_layers = 2 + hidden_layers;
    values.resize(all_layers);
    values[0].resize(input_layer_size);
    for (int i = 1; i < all_layers - 1; i++) values[i].resize(hidden_layer_size);
    values.back().resize(output_layer_size);
    
    int all_weights = all_layers - 1;
    weights.resize(all_weights);
    weights[0].resize(input_layer_size);
    for (int i = 1; i < all_weights; i++) weights[i].resize(hidden_layer_size);
    for (int i = 0; i < all_weights; i++)
    {
      for (int j = 0; j < weights[i].size(); j++)
        weights[i][j].resize(values[i + 1].size());
    }
    
    set_weights();
  }
  
  void set_input(const std::vector<float> &values)
  {
    assert(this->values[0].size() == values.size());
    
    this->values[0] = values;
  }
  
  void set_weights()
  {
    for (auto &x : weights)
      for (auto &y : x)
        for (auto &z : y)
          z = Ask::random(0.f, 1.f);
  }
  
  void calculate_output()
  {
    for (int x = 1; x < values.size(); x++)
      for (int y = 0; y < values[x].size(); y++)
        values[x][y] = 0.f;
    
    for (int x = 0; x < weights.size(); x++)
      for (int y = 0; y < weights[x].size(); y++)
        for (int z = 0; z < weights[x][y].size(); z++)
          values[x + 1][y] += values[x][y] * weights[x][y][z];
    
    for (auto &i : values.back())
      i = Ask::squeeze(i);
    
//    for (auto &i : output)
//      i->value = Ask::squeeze(i->value);

//    std::cout << std::fixed << values.back()[0] << ", " << values.back()[1] << ", " << values.back()[2] << "\n";
  
  }
  
  void render(sf::RenderTexture &texture)
  {
    texture.clear();
    static float r = 8;
    static sf::CircleShape c(r);
    c.setOrigin(c.getRadius(), c.getRadius());
    
    // koblinger
    for (int x = 0; x < weights.size(); x++)
      for (int y = 0; y < weights[x].size(); y++)
        for (int z = 0; z < weights[x][y].size(); z++)
        {
          sf::Vector2f a = {
              Ask::distribute(values.size(), texture.getSize().x, x),
              Ask::distribute(values[x].size(), texture.getSize().y, y)};
          
          sf::Vector2f b = {
              Ask::distribute(values.size(), texture.getSize().x, x + 1),
              Ask::distribute(values[x + 1].size(), texture.getSize().y, z)};
          
          texture.draw(line(a, b, weights[x][y][z] * 4,
                            {255, 240, 240, (sf::Uint8) (255 * weights[x][y][z] * values[x][y])}));
        }
    
    // kuler
    for (int x = 0; x < values.size(); x++)
      for (int y = 0; y < values[x].size(); y++)
      {
        c.setPosition({
            Ask::distribute(values.size(), texture.getSize().x, x),
            Ask::distribute(values[x].size(), texture.getSize().y, y)});
        c.setFillColor({255, 255, 255, (sf::Uint8)(255 * values[x][y])});
        texture.draw(c);
      }
    
    
    
//    for (int i = 0; i < values[0].size(); i++)
//    {
//      sf::Vector2f a = {vec_in.x, vec_in.y * (i + 1)};
//
//      for (int j = 0; j < input[i]->outputs.size(); j++)
//      {
//        sf::Vector2f b = {vec_out.x, vec_out.y * (j + 1)};
//        texture.draw(line
//        (a, b,
//         input[i]->outputs[j].strength * 4,
//         {255, 240, 240, (sf::Uint8) (255 * input[i]->outputs[j].strength * input[i]->value)}));
//      }
//      c.setPosition(a);
//      c.setFillColor({255, 255, 255, (sf::Uint8)(255 * input[i]->value)});
//      texture.draw(c);
//    }
//
//    for (int i = 0; i < output.size(); i++)
//    {
//      sf::Vector2f pos = {vec_out.x, vec_out.y * (i + 1)};
//      c.setPosition(pos);
//      c.setFillColor({255, 255, 255, (sf::Uint8)(255 * output[i]->value)});
//      texture.draw(c);
//    }
    
    
    texture.draw(c);
  }
};

class Smart_brain : public Brain
{
public:
  Instructions think(const Senses &senses) override
  {
    Instructions a;
    
    std::vector<float> values(senses.reseptors);
//    std::vector<float> values = {1.f, 1.f, 1.f};
    values.push_back(senses.pulse);
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
  Smart_brain() : neural_net(4, 3)
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
};

#endif //ECO_SMART_BRAIN_H
