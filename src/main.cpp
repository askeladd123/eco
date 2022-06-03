
/*
 * Ansvar for flyt i programmet
 */

/*
 * TODO
 * teste collision
 * brain
 * reseptors
 * Har lyst å lage brain polymorphic så jeg kan bytte den ut lett, men crasher
 * quadtree
 * visualisere bounds
 * blob animasjon
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
  Graphics_image::init();
  if (!ImGui::SFML::Init(window))
  {
    std::cout << "vinduet funka visst ikke\n";
    return -1;
  }
  
  fps fps;
  bool play = true;
  bool blob_brush = false;
  World world;
  
  sf::CircleShape c1, c2;
  c1.setRadius(60);
  c2.setRadius(60);
  
  enum states {MAIN, PHYSICS};
  states ImGui_state = MAIN;
  
  int ImGui_items = 1;
  
  world.add(World::BLOB, 100, 100);
  
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
      
        case sf::Event::MouseButtonPressed:
          if (blob_brush)
          {
            blob_brush = false;
            auto m = mouse();
            world.add(World::BLOB, m.x, m.y, ImGui_items);
          }
          break;
      }
    }
  
    ImGui::SFML::Update(window, deltaClock.restart());
  
    ImGui::Begin("Control Panel bitches", NULL, ImGuiWindowFlags_MenuBar);
  
    if (ImGui::BeginMenuBar())
    {
      if (ImGui::BeginMenu("menu"))
      {
        if (ImGui::MenuItem("main"))
        {
          ImGui_state = MAIN;
        }
        
        if (ImGui::MenuItem("physics"))
        {
          ImGui_state = PHYSICS;
        }
        
        ImGui::EndMenu();
      }
      
      switch (ImGui_state)
      {
        case MAIN:
          if (play)
            play = !ImGui::Button("pause");
  
          else play = ImGui::Button("play");
    
          if (ImGui::Button("slower"))
            window.setFramerateLimit(fps.decreased());
    
          if (ImGui::Button("normal speed"))
            window.setFramerateLimit(fps.normal());
    
          if (ImGui::Button("faster"))
            window.setFramerateLimit(fps.increased());
          
          break;
          
        case PHYSICS:
          if (ImGui::Button("add blob"))
            blob_brush = !blob_brush;
          
          if (ImGui::BeginMenu(std::to_string(ImGui_items).c_str()))
          {
            if (ImGui::MenuItem("1 blob"))
              ImGui_items = 1;
            
            if (ImGui::MenuItem("10 blob"))
              ImGui_items = 10;
            
            if (ImGui::MenuItem("50 blobs"))
              ImGui_items = 50;
            
            ImGui::EndMenu();
          }
          
          break;
      }
  
      ImGui::Text("fps: %1.0f", ImGui::GetIO().Framerate);
      
      ImGui::EndMenuBar();
    }
  
    switch (ImGui_state)
    {
      case PHYSICS:
        ImGui::SliderFloat("stopping threshold", &world.basically_zero, 0.f, 1.f);
        ImGui::SliderFloat("friction", &world.friction_c, 0.f, 1.f);
        ImGui::SliderFloat("drag", &world.drag_c, 0.f, 0.2f);
        break;
    }
    
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
        view.zoom(1.0f - view_zoom_amount * ImGui::GetIO().DeltaTime * 40);
        
      else view_offset_y -= view_movement_speed * ImGui::GetIO().DeltaTime * 40;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        view.zoom(1.0f + view_zoom_amount * ImGui::GetIO().DeltaTime * 40);
      
      else view_offset_y += view_movement_speed * ImGui::GetIO().DeltaTime * 40;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      view_offset_x += view_movement_speed * ImGui::GetIO().DeltaTime * 40;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      view_offset_x -= view_movement_speed * ImGui::GetIO().DeltaTime * 40;
    
    view.setCenter(sf::Vector2f(view_offset_x, view_offset_y));
    window.setView(view);
    
    // grafikk
    window.clear();
    
    if (0)
    {
      c1.setPosition({mouse().x - c1.getRadius(), mouse().y - c1.getRadius()});
  
      if (
          Ask::Physics::intersects(
              Ask::Physics::Circle(c1.getPosition().x, c1.getPosition().y, 69),
              Ask::Physics::Circle(c2.getPosition().x, c2.getPosition().y, 69))
          )
      {
        c1.setFillColor(sf::Color::Red);
        c2.setFillColor(sf::Color::Red);
      } else
      {
        c1.setFillColor(sf::Color::White);
        c2.setFillColor(sf::Color::White);
      }
      window.draw(c1);
      window.draw(c2);
    }
  
    world.render();
    ImGui::SFML::Render(window);
    
    window.display();
  }
  
  ImGui::SFML::Shutdown();
  
  return 0;
}