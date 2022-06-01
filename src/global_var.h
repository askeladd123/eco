//
// Created by askso on 30/05/2022.
//

#ifndef ECO_GLOBAL_VAR_H
#define ECO_GLOBAL_VAR_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

sf::View view;
sf::RenderWindow window;
sf::Clock time_since_startup;
unsigned long long ticks_since_startup = 0;
int view_offset_x = 0, view_offset_y = 0;
int view_height = 800;
int view_movement_speed = 6;
float view_zoom_amount = 0.01;

#endif //ECO_GLOBAL_VAR_H
