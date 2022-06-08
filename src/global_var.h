//
// Created by askso on 30/05/2022.
//

#ifndef ECO_GLOBAL_VAR_H
#define ECO_GLOBAL_VAR_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <list>
#include "files.h"

sf::View view;
sf::RenderWindow window;
sf::Clock time_since_startup;
Files files;
unsigned long long ticks_since_startup = 0;
int view_offset_x = -350, view_offset_y = 0;
int view_height = 800;
int view_movement_speed = 6;
float view_zoom_amount = 0.01;
int last_pos_y;
bool hovered = false;

// imgui
int blob_brush_amount = 0;
bool hitbox_blob = false;
bool hitbox_mouse = false;
bool pls_add = false;
sf::Color hitbox_hit(100, 200, 100, 100);
sf::Color hitbox_unhit(200, 100, 100, 100);

#endif //ECO_GLOBAL_VAR_H
