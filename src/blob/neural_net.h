//
// Created by askso on 01/07/2022.
//

#ifndef ECO_NEURAL_NET_H
#define ECO_NEURAL_NET_H

#include <vector>
#include <cassert>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ask/math.h"
#include "global_func.h"


class Neural_net
{
  typedef std::vector<std::vector<float>> matrix2d_float;
  typedef std::vector<std::vector<std::vector<float>>> matrix3d_float;

public:
  matrix2d_float values;
  matrix3d_float weights;

public:
  Neural_net(int input_layer_size, int output_layer_size, int hidden_layers = 0, int hidden_layer_size = 10)
  {
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
  
  void set_weights()
  {
    for (auto &x : weights)
      for (auto &y : x)
        for (auto &z : y)
          z = Ask::random(0.f, 1.f);
  }
  
  void set_input(const std::vector<float> &values)
  {
    assert(this->values[0].size() == values.size());
    
    this->values[0] = values;
  }
  
  
  void calculate_output()
  {
    // flush values
    for (int x = 1; x < values.size(); x++)
      for (int y = 0; y < values[x].size(); y++)
        values[x][y] = 0.f;
    
    // fire!
    for (int x = 0; x < weights.size(); x++)
      for (int y = 0; y < weights[x].size(); y++)
        for (int z = 0; z < weights[x][y].size(); z++)
          values[x + 1][z] += values[x][y] * weights[x][y][z];
    
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
    
//    std::cout << std::fixed;
//    for (auto &i : values.back())
//      std::cout << i << "\t";
//    std::cout << "\n";
    
//    texture.draw(c);
  }
};

#endif //ECO_NEURAL_NET_H
