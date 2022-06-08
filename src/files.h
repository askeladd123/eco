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
    sf::Image error_ram;
    error_ram.create(64, 64, sf::Color::Red);
    error.loadFromImage(error_ram);
    
    sf::Image blob_ram;
    if (!blob_ram.loadFromFile("res/blob.png"))
    {
      std::cout << "failed to load res/blob.png\n";
      blob = error;
    }
    blob.loadFromImage(blob_ram);
    simple_blob.setTexture(blob);
    simple_blob.setScale({0.2f, 0.2f});
    simple_blob.setOrigin({64, 64});
    
    sf::Image concrete_ram;
    if (!concrete_ram.loadFromFile("res/concrete.png"))
    {
      std::cout << "failed to load res/concrete.png\n";
      concrete = error;
    }
    concrete.loadFromImage(concrete_ram);
    
    sf::Image tiles_ram;
    if (!tiles_ram.loadFromFile("res/tiles.png"))
    {
      std::cout << "failed to load res/tiles.png\n";
      tiles = error;
    }
    tiles.loadFromImage(tiles_ram);
    
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

private:
  std::vector<std::string> first_names, last_names;
  sf::Texture error, blob, concrete, tiles;
};

#endif //ECO_FILES_H
