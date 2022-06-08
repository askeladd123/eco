//
// Created by askso on 08/06/2022.
//

#ifndef ECO_FILES_H
#define ECO_FILES_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "ask/praktisk.h"

/// laster alle filer, og er static, så alle har tilgang
class Files
{
public:
  sf::Sprite simple_blob;
  sf::Texture error, blob, concrete, tiles;

private:
  std::vector<std::string> first_names, last_names;
  sf::Image error_ram, blob_ram, concrete_ram, tiles_ram;
  
  /*
   * sf::Image: RAM - muligheter for å redigere
   * sf::Texture: GPU-RAM - rask å tegne - tar lang tid å lage/sende
   * sf::Sprite: window.draw(sprite)
   */
public:
  Files()
  {
    using namespace std;
    
    // bilder - laster de først opp i RAM, det må man for å redigere de bra
    error_ram.create(64, 64, sf::Color::Red);
    error.loadFromImage(error_ram);

    if (!blob_ram.loadFromFile("res/blob.png"))
    {
      std::cout << "failed to load res/blob.png\n";
      blob = error;
    }
    blob.loadFromImage(blob_ram);
    add_color(blob_ram, {10, 10, 10}, blob);
    simple_blob.setTexture(blob);
    simple_blob.setScale({0.2f, 0.2f});
    simple_blob.setOrigin({64, 64});
    
    if (!concrete_ram.loadFromFile("res/concrete.png"))
    {
      std::cout << "failed to load res/concrete.png\n";
      concrete = error;
    }
    concrete.loadFromImage(concrete_ram);
    concrete.setRepeated(true);
    sub_color(concrete_ram, concrete, 0, 0, 0, 160);
    
    if (!tiles_ram.loadFromFile("res/tiles.png"))
    {
      std::cout << "failed to load res/tiles.png\n";
      tiles = error;
    }
    tiles.loadFromImage(tiles_ram);
    tiles.setRepeated(true);
    sub_color(tiles_ram, tiles, 84, 88, 80);
    
    // tekst
    ifstream file("res/names.txt");
    if (file.is_open())
    {
      string line;
      while (getline(file, line))
      {
        int pos;
        if ((pos = line.find(' ')) == string::npos)
          throw logic_error("names.txt in wrong format: missing space character");
        
        first_names.push_back(line.substr(0, pos));
        line.erase(0, pos + 1);
        last_names.push_back(line);
      }
    }
    else
    {
      std::cout << "couldn't load file names.txt\n";
    }
  }

public:
  std::string random_name()
  {
    if (first_names.empty())
      return "names not loaded";
    
    return
        first_names[(int)Ask::random(-0.49, first_names.size() - 0.01)] +
        " " +
        first_names[(int)Ask::random(-0.49, first_names.size() - 0.01)];
  }
  
  static void add_color(sf::Image &image, sf::Color color, sf::Texture &texture)
  {
//    throw std::runtime_error("files::add_color: funksjon ikke skrevet enda\n");
    for (int x = 0; x < image.getSize().x; x++)
      for (int y = 0; y < image.getSize().y; y++)
      {
        auto temp_color = image.getPixel(x, y);
        temp_color.r = 255 - color.r < temp_color.r ? 255 : temp_color.r + color.r;
        temp_color.g = 255 - color.g < temp_color.g ? 255 : temp_color.g + color.g;
        temp_color.b = 255 - color.b < temp_color.b ? 255 : temp_color.b + color.b;
        image.setPixel(x, y, temp_color);
      }
    texture.update(image);
  }
  
  static void sub_color(sf::Image &image, sf::Texture &texture, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 0)
  {
    for (int x = 0; x < image.getSize().x; x++)
      for (int y = 0; y < image.getSize().y; y++)
      {
        auto temp_color = image.getPixel(x, y);
        temp_color.r = (temp_color.r - r) * (r <= temp_color.r);
        temp_color.g = (temp_color.g - g) * (g <= temp_color.g);
        temp_color.b = (temp_color.b - b) * (b <= temp_color.b);
        temp_color.a = (temp_color.a - a) * (a <= temp_color.a);
        image.setPixel(x, y, temp_color);
      }
    texture.update(image);
  }
};

#endif //ECO_FILES_H
