//
// Created by askso on 31/05/2022.
//

#ifndef ECO_GLOBAL_DEF_H
#define ECO_GLOBAL_DEF_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>

#include "ask/math.h"
#include "ask/errors.h"

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

class Entity
{
public:
  enum Type {BLOB} type;
  
protected:
  Entity(Type type) : type(type){};
};

#endif //ECO_GLOBAL_DEF_H
