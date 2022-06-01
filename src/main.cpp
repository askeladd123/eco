
/*
 * Ansvar for flyt i programmet
 */

/*
 * TODO
 * smooth bevegelse på View
 * collision
 * brain
 * reseptors
 * lære imgui
 * Har lyst å lage brain polymorphic så jeg kan bytte den ut lett, men crasher
 * quadtree
 */

// standard lib
#include <iostream>

// extern lib
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

// mine includes
#include "global_var.h"
#include "global_def.h"
#include "world.h"

int main() {
  window.create(sf::VideoMode(sf::Vector2u(view_height, view_height)), "ImGui + SFML = <3");
  view_resize();
  window.setFramerateLimit(60);
  if (!ImGui::SFML::Init(window))
  {
    std::cout << "vinduet funka visst ikke\n";
    return -1;
  }
  
  fps fps;
  bool play = true;
  bool blob_brush = false;
  World world;
  
  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);
      
      switch(event.type)
      {
        case sf::Event::Closed:
          window.close();
          break;
          
        case sf::Event::Resized:
          view_resize();
          break;
          
        case sf::Event::MouseButtonPressed:
          if (blob_brush)
          {
            blob_brush = false;
            auto mouse_window = sf::Mouse::getPosition(window);
            auto mouse_view = window.mapPixelToCoords(mouse_window);
            world.add(World::BLOB).and_move(mouse_view.x, mouse_view.y);
          }
          break;
      }
    }
    
    ImGui::SFML::Update(window, deltaClock.restart());
    
    ImGui::Begin("Toolbars ;)");
    
    ImGui::Text("gun på vettu");
    
    if (play)
      play = !ImGui::Button("pause");
    
    else play = ImGui::Button("play");
    
    if (ImGui::Button("slower"))
      window.setFramerateLimit(fps.decreased());
    
    if (ImGui::Button("normal speed"))
      window.setFramerateLimit(fps.normal());
    
    if (ImGui::Button("faster"))
      window.setFramerateLimit(fps.increased());
    
    if (ImGui::Button("blob"))
      blob_brush = !blob_brush;
    
    ImGui::Text("fps: %1.0f", ImGui::GetIO().Framerate);
    
    ImGui::End();
    
    // logikk
    if (play)
    {
      ticks_since_startup++;
      world.tick();
    }
    
    // flytte på View
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        view.zoom(1.0f - view_zoom_amount);
        
      else view_offset_y -= view_movement_speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        view.zoom(1.0f + view_zoom_amount);
      
      else view_offset_y += view_movement_speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      view_offset_x += view_movement_speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      view_offset_x -= view_movement_speed;
    
    view.setCenter(sf::Vector2f(view_offset_x, view_offset_y));
    window.setView(view);
    
    // grafikk
    window.clear();
    
    world.render();
    ImGui::SFML::Render(window);
    
    window.display();
  }
  
  ImGui::SFML::Shutdown();
  
  return 0;
}