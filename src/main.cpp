
/*
 * Ansvar for flyt i programmet
 */

/*
 * TODO
 * views
 *
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
#include "globals.h"
#include "mess.h"
#include "world.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 800)), "ImGui + SFML = <3");
  window.setFramerateLimit(60);
  if (!ImGui::SFML::Init(window))
  {
    std::cout << "vinduet funka visst ikke\n";
    return -1;
  }
  
  fps fps;
  bool play = true;
  bool blob_brush = false;
  world world;
  
  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);
      
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      
      if (event.type == sf::Event::MouseButtonPressed)
      {
        if (blob_brush)
        {
          blob_brush = false;
          world.add(world::BLOB).and_move(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        }

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
    
    ImGui::End();
    
    if (play)
      world.tick();
    
    window.clear();
    
    world.render(window);
    ImGui::SFML::Render(window);
    
    window.display();
  }
  
  ImGui::SFML::Shutdown();
  
  return 0;
}