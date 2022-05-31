
/*
 * Ansvar for flyt i programmet
 */

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>
#include "SFML/Window/VideoMode.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 800)), "ImGui + SFML = <3");
  window.setFramerateLimit(60);
  if (!ImGui::SFML::Init(window))
  {
    std::cout << "vinduet funka visst ikke\n";
    return -1;
  }
  
  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);
      
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    
    ImGui::SFML::Update(window, deltaClock.restart());
    
    ImGui::Begin("Toolbars ;)");
    
    ImGui::Text("gun på vettu");
    
    ImGui::End();
    
    window.clear();
    ImGui::SFML::Render(window);
    window.display();
  }
  
  ImGui::SFML::Shutdown();
  
  return 0;
}