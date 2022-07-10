
/*
 * Ansvar for flyt i programmet
 */

/*
 * TODO
 *  blob animasjon: tips, bruk ticks_since_startup og modulo
 *  animasjon generell: noe som varer gitt mengde frames: sender animasjon til animasjon objekt
 *  insekter kan interacte med spiller
 *  README
 *  rydde opp i unødvedige globals
 *  automatisk skygger
 */

// standard lib
#include <iostream>
#include <numeric>

// extern lib
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include <box2d/box2d.h>

// mine includes
#include "global_var.h"
#include "global_def.h"
#include "game_engine.h"
#include "gui.h"

int main() {
  assert(CHAR_BIT * sizeof (float) == 32);// box2d trenger float32
  {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(view_height * 2, view_height), "insekter og kult", sf::Style::Default, settings);
  }
  view_resize();
  view.zoom(1.1);
  window.setFramerateLimit(60);
  if (!ImGui::SFML::Init(window))
  {
    std::cout << "vinduet funka visst ikke\n";
    return -1;
  }
  
//  Game_engine game_engine;
  game_engine.add(Game_engine::BLOB, 100, 100);
  
  sf::Clock deltaClock;
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      ImGui::SFML::ProcessEvent(event);
    
      switch (event.type)
      {
        case sf::Event::Closed:
          window.close();
          break;
      
        case sf::Event::Resized:
          view_resize();
          break;
      
        static int mouse_down_x = 0;
        static int mouse_down_y = 0;
        static bool mouse_down = false;
        
        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Left)
          {
  
            if (!mouse_down && !ImGui::IsAnyItemActive())
            {
              mouse_down = true;
              mouse_down_x = mouse.x;
              mouse_down_y = mouse.y;
            }
          }
          
          if (event.mouseButton.button == sf::Mouse::Right)
          {
            selected_entity = game_engine.get_entity_at(mouse.x, mouse.y);
          }
          break;
          
        case sf::Event::MouseButtonReleased:
          mouse_down = false;
          if (object_dropped != Game_engine::NONE)
            pls_add = true;
          break;
          
        case sf::Event::MouseMoved:
          if (mouse_down && !ImGui::IsAnyItemActive())
          {
            view_offset_x = view.getCenter().x + mouse_down_x - mouse.x;
            view_offset_y = view.getCenter().y + mouse_down_y - mouse.y;
          }
          break;
          
        case sf::Event::MouseWheelScrolled:
        {
          if (!ImGui::IsAnyItemActive())
            view.zoom(1 + event.mouseWheelScroll.delta * - 0.03);
        }
      }
    }
  
    // ====================== V === imgui === V ====================== \\
    
    ImGui::SFML::Update(window, deltaClock.restart());
  
    ImGui::ShowDemoWindow();
    
    gui();
    
    // ====================== A === imgui === A ====================== \\
    
    if (play)
      game_engine.tick();
  
    // logikk
    if (pls_add && object_dropped != Game_engine::NONE)
    {
      game_engine.add(object_dropped, mouse.x, mouse.y, object_drop_amount);
      pls_add = false;
      object_dropped = Game_engine::NONE;
      object_drop_amount = 1;
    }
    
    // flytte på View
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        view.zoom(1.0f - view_zoom_amount * ImGui::GetIO().DeltaTime * 40);
        
      else view_offset_y -= view_movement_speed * ImGui::GetIO().DeltaTime * 40;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        view.zoom(1.0f + view_zoom_amount * ImGui::GetIO().DeltaTime * 40);
      
      else view_offset_y += view_movement_speed * ImGui::GetIO().DeltaTime * 40;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      view_offset_x += view_movement_speed * ImGui::GetIO().DeltaTime * 40;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      view_offset_x -= view_movement_speed * ImGui::GetIO().DeltaTime * 40;
    
    view.setCenter({(float)view_offset_x, (float)view_offset_y});
    window.setView(view);
  
    if (take_control && blob_is_selected())
    {
      auto &blob = blob_get();
      
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        blob.logic.body->ApplyLinearImpulseToCenter({0, meters(-1)}, true);

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        blob.logic.body->ApplyLinearImpulseToCenter({0, meters(1)}, true);

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        blob.logic.body->ApplyLinearImpulseToCenter({meters(-1), 0}, true);

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        blob.logic.body->ApplyLinearImpulseToCenter({meters(1), 0}, true);

    }
    
    // grafikk
    window.clear();
  
    game_engine.render();
    
    ImGui::SFML::Render(window);
    
    window.display();
  }
  
  ImGui::SFML::Shutdown();
  
  return 0;
}