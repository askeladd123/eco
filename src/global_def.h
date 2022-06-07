//
// Created by askso on 31/05/2022.
//

#ifndef ECO_GLOBAL_DEF_H
#define ECO_GLOBAL_DEF_H

#include <SFML/Graphics.hpp>
#include <fstream>

#include "ask/physics.h"
#include "ask/praktisk.h"
#include "global_var.h"

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

void view_resize()
{
  float ratio = (float)window.getSize().x / window.getSize().y;
  view.setSize(sf::Vector2f(view_height * ratio, view_height));
}

sf::Vector2f mouse()
{
  auto mouse_window = sf::Mouse::getPosition(window);
  return window.mapPixelToCoords(mouse_window);
}

/// sørger for at firkanten du tegner er hitboxen
sf::RectangleShape &fit_to_bounds(sf::RectangleShape &fit_this, const Ask::Physics::Tile &to_this)
{
  fit_this.setSize({(float)to_this.r_x * 2, (float)to_this.r_y * 2});
  fit_this.setOrigin({(float)to_this.r_x, (float)to_this.r_y});
  fit_this.setPosition({(float)to_this.center.x, (float)to_this.center.y});
  return fit_this;
}

/// sørger for at sirkelen du tegner er hitboxen
sf::CircleShape &fit_to_bounds(sf::CircleShape &fit_this, const Ask::Physics::Circle &to_this)
{
  fit_this.setRadius(to_this.r);
  fit_this.setOrigin({fit_this.getRadius(), fit_this.getRadius()});
  fit_this.setPosition({(float)to_this.center.x, (float)to_this.center.y});
  return fit_this;
}

///kjør load først
class Names
{
public:
  static void load()
  {
    using namespace std;
    
    ifstream file("res/names.txt");
    if (file.is_open())
    {
      string line;
      while (getline(file, line))
      {
        int pos;
        if ((pos = line.find(' ')) == string::npos)
          throw logic_error("names.txt in wrong format: missing space character");
        
        first.push_back(line.substr(0, pos));
        line.erase(0, pos + 1);
        last.push_back(line);
      }
    }
    else
    {
      std::cout << "couldn't load file names.txt\n";
    }
  }
  
public:
  static std::string random()
  {
    if (first.empty())
      return "names not loaded";
    
    return
    first[(int)Ask::random(-0.49, first.size() - 0.01)] +
    " " +
    first[(int)Ask::random(-0.49, first.size() - 0.01)];
  }

private:
  static std::vector<std::string> first, last;
};

std::vector<std::string> Names::first, Names::last;


#endif //ECO_GLOBAL_DEF_H
