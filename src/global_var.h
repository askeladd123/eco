//
// Created by askso on 30/05/2022.
//

#ifndef ECO_GLOBAL_VAR_H
#define ECO_GLOBAL_VAR_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <list>
#include "global_def.h"
#include "files.h"

sf::View view;
sf::RenderWindow window;
sf::Clock time_since_startup;
sf::Color hitbox_hit(100, 200, 100, 100);
sf::Color hitbox_unhit(200, 100, 100, 100);
Files files;
unsigned long long ticks_since_startup = 0;
int view_offset_x = -350, view_offset_y = 0;
int view_height = 800;
int view_movement_speed = 6;
float view_zoom_amount = 0.01;
int last_pos_y;
int mouse_hitbox_type = 0;
enum {CIRCLE, LINE, RAY};
int object_drop_amount = 0;
bool hitbox_blob = false;
bool hitbox_static_objects = false;
bool hitbox_mouse = false;
bool pls_add = false;
float world_width_meters = 40;
int world_width = 800;
int PPM = 32;
bool selecting = false;
Entity *selected_entity = nullptr;
bool take_control = false;
bool play = true;
float friction_c = 0.5f;
float friction_c_r = 0.5f;

int object_dropped;
b2World world({0, 0});
class Game_engine;
extern Game_engine game_engine;
fps fps;

#endif //ECO_GLOBAL_VAR_H
