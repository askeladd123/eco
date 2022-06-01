//
// Created by askso on 30/05/2022.
//

#ifndef ECO_GLOBAL_DEF_H
#define ECO_GLOBAL_DEF_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

sf::View view;
sf::RenderWindow window;
int view_offset_x = 0, view_offset_y = 0;
int view_height = 800;
int view_movement_speed = 6;
float view_zoom_amount = 0.01;

void view_resize()
{
  float ratio = (float)window.getSize().x / window.getSize().y;
  view.setSize(sf::Vector2f(view_height * ratio, view_height));
}

#endif //ECO_GLOBAL_DEF_H
