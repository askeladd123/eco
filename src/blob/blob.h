//
// Created by askso on 30/05/2022.
//
#ifndef ECO_BLOB_H
#define ECO_BLOB_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "common.h"
#include "logic.h"
#include "brain.h"
#include "graphics.h"

class Blob
{
public:
  Logic logic;
  Brain brain;
  Graphics graphics;
      
  /**
   * @brief Enderer hovedsaklig på fart og rotasjon til en blob
   */
  void think()
  {
    auto senses = logic.pull();
    
    auto instructions = brain.think(senses);
    
    logic.push(instructions);
    
    std::cout << logic.x << ", " << logic.y << "\n";
  }
  
  void render(sf::RenderWindow &window)
  {
    graphics.render(window, logic);
  }
};

#endif
