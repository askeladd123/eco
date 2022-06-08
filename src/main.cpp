
/*
 * Ansvar for flyt i programmet
 */

/*
 * TODO
 * collisjon: flytte kuler fra hverandre
 * brain
 * reseptors
 * Har lyst å lage brain polymorphic så jeg kan bytte den ut lett, men crasher
 * quadtree
 * blob animasjon
 * select blob
 * imgui graf, tabs, drag drop
 * insekter kan interacte med spiller
 * navigasjon: mulighet for mus også: dra og scroll
 * README
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
  window.create(sf::VideoMode(view_height, view_height), "ImGui + SFML = <3");
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
          break;
          
        case sf::Event::MouseButtonReleased:
          if (blob_brush_amount)
            pls_add = true;
      }
    }
  
    // ====================== V === imgui === V ====================== \\
    
    ImGui::SFML::Update(window, deltaClock.restart());
  
//    ImGui::ShowDemoWindow();
    
    ImGui::Begin("Control Panel bitches", NULL, ImGuiWindowFlags_MenuBar);
    
    if (ImGui::BeginMenuBar())
    {
      if (ImGui::BeginMenu("menu"))
      {
        if (ImGui::MenuItem("main"))
          ImGui_state = MAIN;
        
        if (ImGui::MenuItem("physics"))
          ImGui_state = PHYSICS;
        
        if (ImGui::MenuItem("one blob"))
          ImGui_state = ONE;
        
        if (ImGui::MenuItem("all blobs"))
          ImGui_state = ALL;
          
        ImGui::EndMenu();
      }
      
      ImGui::Text("\t");
      
      if (play)
        play = !ImGui::Button("pause");
  
      else play = ImGui::Button("play");
  
      if (ImGui::Button("slower"))
        window.setFramerateLimit(fps.decreased());
  
      if (ImGui::Button("normal speed"))
        window.setFramerateLimit(fps.normal());
  
      if (ImGui::Button("faster"))
        window.setFramerateLimit(fps.increased());
  
      ImGui::Text("\tfps: %1.0f", ImGui::GetIO().Framerate);
  
      ImGui::EndMenuBar();
    }
  
    switch (ImGui_state)
    {
      case MAIN:
        ImGui::Spacing();
        ImGui::Text("If you love fake insects, this program is for you. \nUse arrowkeys to move, and Ctrl + Up or Ctrl + Down to zoom.");
        break;
      
      case PHYSICS:
        ImGui::Text("blobs: %i", world.blobs.size());
        
        ImGui::Button(" 1 blob ");
        if (ImGui::BeginDragDropSource())
        {
          blob_brush_amount = 1;
          ImGui::BeginTooltip();
          ImGui::SetTooltip("1");
          ImGui::EndTooltip();
          ImGui::EndDragDropSource();
        }
        ImGui::SameLine();
    
        ImGui::Button(" 10 blobs ");
        if (ImGui::BeginDragDropSource())
        {
          blob_brush_amount = 10;
          ImGui::BeginTooltip();
          ImGui::SetTooltip("10");
          ImGui::EndTooltip();
          ImGui::EndDragDropSource();
        }
        ImGui::SameLine();
        
        ImGui::Button(" 50 blobs ");
        if (ImGui::BeginDragDropSource())
        {
          blob_brush_amount = 50;
          ImGui::BeginTooltip();
          ImGui::SetTooltip("50");
          ImGui::EndTooltip();
          ImGui::EndDragDropSource();
        }
        
        ImGui::Spacing();
        
//        if (ImGui::Button(((!blob_brush)? " add" : " adding")))
//          blob_brush = !blob_brush;
//
//        ImGui::SameLine();
//        if (ImGui::BeginMenu(
//            (
//                std::to_string(ImGui_blob_brush_amount) +
//                ((ImGui_blob_brush_amount == 1) ? " blob" : " blobs")
//                ).c_str()))
//        {
//          if (ImGui::MenuItem("1 blob"))
//          {
//            ImGui_blob_brush_amount = 1;
//            blob_brush = true;
//          }
//
//          if (ImGui::MenuItem("10 blobs"))
//          {
//            ImGui_blob_brush_amount = 10;
//            blob_brush = true;
//          }
//
//          if (ImGui::MenuItem("50 blobs"))
//          {
//            ImGui_blob_brush_amount = 50;
//            blob_brush = true;
//          }
//
//          ImGui::EndMenu();
//        }
        
        ImGui::Separator();
        
        ImGui::SliderFloat("stopping threshold", &world.basically_zero, 0.f, 1.f);
        ImGui::SliderFloat("friction", &world.friction_c, 0.f, 1.f);
        ImGui::SliderFloat("drag", &world.drag_c, 0.f, 0.2f);
        
        ImGui::BeginTabBar("tabs");
        ImGui::TabItemButton("kjor");
        ImGui::EndTabBar();
        
        if (ImGui::CollapsingHeader("hitboxes"))
        {
          ImGui::Checkbox("blobs", &hitbox_blob);
//          ImGui::Checkbox("quadtree", nullptr);
          ImGui::Checkbox("mouse", &hitbox_mouse);
//          ImGui::SameLine();
//          ImGui::BeginMenu("hitbox shape");
//          ImGui::MenuItem("circle");
//          ImGui::MenuItem("square");
//          ImGui::EndMenu();
        }
        break;
        
      case ALL:
        ImGui::Text("%i", world.blobs.size());
        if (ImGui::IsItemHovered())
        {
          ImGui::BeginTooltip();
          ImGui::Text("help");
          ImGui::EndTooltip();
        }
        
        if (ImGui::CollapsingHeader("list"))
        {
          if (ImGui::BeginTable("select blob", 3))
          {
            static int selected_blob = -1;
            static bool selected = {false};
    
            ImGui::TableNextColumn();
            ImGui::Text("name");
            ImGui::TableNextColumn();
            ImGui::Text("x");
            ImGui::TableNextColumn();
            ImGui::Text("y");
    
            for (int i = 0; i < world.blobs.size(); i++)
            {
              char label[32];
              sprintf(label, "%s", world.blobs[i].name.c_str());
              ImGui::TableNextRow();
              ImGui::TableNextColumn();
              if (ImGui::Selectable(label, selected_blob == i, ImGuiSelectableFlags_SpanAllColumns))
                selected_blob = i;
      
              ImGui::TableNextColumn();
              ImGui::Text("%i", (int) world.blobs[i].logic.x);
              ImGui::TableNextColumn();
              ImGui::Text("%i", (int) world.blobs[i].logic.y);
            }
            ImGui::EndTable();
          }
        }
        
        break;
    }
    
    ImGui::End();
    
    // ====================== A === imgui === A ====================== \\
    
    
    
    if (play)
    {
      ticks_since_startup++;
      world.tick();
    }
  
    // logikk
    if (pls_add)
    {
      pls_add = false;
      auto m = mouse();
      world.add(World::BLOB, m.x, m.y, blob_brush_amount);
      blob_brush_amount = 0;
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
    
    view.setCenter(sf::Vector2f(view_offset_x, view_offset_y));
    window.setView(view);
    
    // grafikk
    window.clear();
  
    world.render();
    ImGui::SFML::Render(window);
  
    if (hitbox_mouse)
    {
      auto m = mouse();
      Ask::Physics::Circle bounds(m.x, m.y, 20);
      sf::CircleShape mouse_gfx;
    
      for (auto& blob: world.blobs)
      {
        if (Ask::Physics::intersects(bounds, blob.graphics.bounds))
        {
          mouse_gfx.setFillColor(hitbox_hit);
          break;
        }
        mouse_gfx.setFillColor(hitbox_unhit);
      }
      window.draw(fit_to_bounds(mouse_gfx, bounds));
    }
    
    window.display();
  }
  
  ImGui::SFML::Shutdown();
  
  return 0;
}