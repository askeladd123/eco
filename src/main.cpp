
/*
 * Ansvar for flyt i programmet
 */

/*
 * TODO
 * brain
 * reseptors
 * Har lyst å lage brain polymorphic så jeg kan bytte den ut lett, men crasher
 * quadtree
 * blob animasjon: tips, bruk ticks_since_startup og modulo
 * select blob
 * grafikk: rediger farger
 * imgui graf, tabs, drag drop
 * insekter kan interacte med spiller
 * README
 * rydde opp i unødvedige globals
 * mus collision typer
 * adde statiske objekter
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
  window.create(sf::VideoMode(view_height * 2, view_height), "ImGui + SFML = <3");
  view_resize();
  view.zoom(1.1);
  window.setFramerateLimit(60);
  if (!ImGui::SFML::Init(window))
  {
    std::cout << "vinduet funka visst ikke\n";
    return -1;
  }
  
  fps fps;
  bool play = true;
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
          static int mouse_down_x = 0;
          static int mouse_down_y = 0;
          
          if (!mouse_down)
          {
            mouse_down = true;
            mouse_down_x = mouse.x;
            mouse_down_y = mouse.y;
          }
          break;
          
        case sf::Event::MouseButtonReleased:
          mouse_down = false;
          if (blob_brush_amount)
            pls_add = true;
          break;
          
        case sf::Event::MouseMoved:
          if (mouse_down)
          {
            view_offset_x = view.getCenter().x + mouse_down_x - mouse.x;
            view_offset_y = view.getCenter().y + mouse_down_y - mouse.y;
          }
          break;
          
        case sf::Event::MouseWheelScrolled:
        {
          view.zoom(1 + event.mouseWheelScroll.delta * - 0.03);
        }
      }
    }
  
    // ====================== V === imgui === V ====================== \\
    
    ImGui::SFML::Update(window, deltaClock.restart());
  
    ImGui::ShowDemoWindow();
    
    ImGui::Begin("Control Panel bitches", NULL, ImGuiWindowFlags_MenuBar);
    
    if (ImGui::IsWindowHovered())
      mouse_down = false;
    
    if (ImGui::BeginMenuBar())
    {
      if (ImGui::BeginMenu("file ellerno"))
      {
        if (ImGui::MenuItem("tull"))
          0;
        
        if (ImGui::MenuItem("et eller annet"))
          0;
          
        ImGui::EndMenu();
      }
      
      ImGui::Text("\t");
      
      static int state = 3;
      if (ImGui::RadioButton("pause", state == 1))
      {
        state = 1;
        play = false;
      }
      
      if (state != 1)
        play = true;
  
      if (ImGui::RadioButton("slower", state == 2))
      {
        state = 2;
        window.setFramerateLimit(fps.decreased());
      }
  
      if (ImGui::RadioButton("normal", state == 3))
      {
        state = 3;
        window.setFramerateLimit(fps.normal());
      }
  
      if (ImGui::RadioButton("faster", state == 4))
      {
        state = 4;
        window.setFramerateLimit(fps.increased());
      }
      
      ImGui::Text("\tfps: %1.0f", ImGui::GetIO().Framerate);
  
      ImGui::EndMenuBar();
    }
  
    ImGui::Text(
        "If you love fake insects, this program is for you. \n"
        "Use arrowkeys to move, and Ctrl + Up or Ctrl + Down to zoom.");
  
    ImGui::Spacing();
    
    ImGui::Text("Use the boxes below to drag in insects:");
    
    ImGui::Spacing();
  
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
    
    ImGui::Text("You can delete them in (insert text) tab below. ");
    
    ImGui::Separator();
    
    if (ImGui::BeginTabBar("select mode"))
    {
      if (ImGui::BeginTabItem("individuals"))
      {
        ImGui::Text("population: %i", world.blobs.size());
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
        ImGui::EndTabItem();
      }
  
      if (ImGui::BeginTabItem("physics"))
      {
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
        ImGui::SliderFloat("stopping threshold", &world.basically_zero, 0.f, 1.f);
        ImGui::SliderFloat("friction", &world.friction_c, 0.f, 0.4f);
  
        ImGui::EndTabItem();
      }
  
      if (ImGui::BeginTabItem("graphics"))
      {
    
        ImGui::EndTabItem();
      }
      ImGui::EndTabBar();
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
      world.add(World::BLOB, mouse.x, mouse.y, blob_brush_amount);
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
    
    view.setCenter({(float)view_offset_x, (float)view_offset_y});
    window.setView(view);
    
    // grafikk
    window.clear();
  
    world.render();
    ImGui::SFML::Render(window);
  
    if (hitbox_mouse)
    {
      Ask::Physics::Circle bounds(mouse.x, mouse.y, 20);
      sf::CircleShape mouse_gfx;
    
      if (!Ask::Physics::intersects({bounds.center.x, bounds.center.y}, world.bounds))
      {
        mouse_gfx.setFillColor(hitbox_hit);
        window.draw(fit_to_bounds(mouse_gfx, bounds));
      }
      else
      {
        for (auto &blob: world.blobs)
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
    }
    
    window.display();
  }
  
  ImGui::SFML::Shutdown();
  
  return 0;
}