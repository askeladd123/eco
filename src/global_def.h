//
// Created by askso on 31/05/2022.
//

#ifndef ECO_GLOBAL_DEF_H
#define ECO_GLOBAL_DEF_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>

#include "ask/matte.h"
#include "ask/workflow.h"

class fps
{
public:
  int get()
  {
    return value;
  }
  
  int normal()
  {
    return value = normal_fps;
  }
  
  int increased()
  {
    if (value == min_fps)
      return value = normal_fps;
    
    else
      return value = max_fps;
  }
  
  int decreased()
  {
    if (value == max_fps)
      return value = normal_fps;
    
    else
      return value = min_fps;
  }

private:
  int value = normal_fps;
  int min_fps = 15;
  int normal_fps = 60;
  int max_fps = 120;
};

#define mouse window.mapPixelToCoords(sf::Mouse::getPosition(window))

typedef unsigned int uint;

class Entity
{
public:
  b2Body *body;
  enum Type {BLOB} type;
  struct FindMe{Type type; unsigned int index;};
  
  virtual void set_index(uint) = 0;
  virtual FindMe get_index() = 0;
  
public:
  Entity(Type type) : type(type)
  {
  
  };
};

#endif //ECO_GLOBAL_DEF_H
