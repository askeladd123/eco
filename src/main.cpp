
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
 * animasjon generell: noe som varer gitt mengde frames: sender animasjon til animasjon objekt
 * select blob
 * insekter kan interacte med spiller
 * README
 * rydde opp i unødvedige globals
 * mus collision typer
 * automatisk skygger
 * rar feil hvor de krasjer og forvinner til verdens ende
 * thread pool
 * stick collision
 */

// standard lib
#include <iostream>

// extern lib
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <numeric>

// mine includes
#include "global_var.h"
#include "global_def.h"
#include "world.h"

int main() {
  {
//    sf::ContextSettings settings;
//    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(view_height * 2, view_height), "ImGui + SFML = <3");//, sf::Style::Default, settings);
  }
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
          static bool mouse_down = false;
    
          if (!mouse_down && !hovered)
          {
            mouse_down = true;
            mouse_down_x = mouse.x;
            mouse_down_y = mouse.y;
          }
          break;
          
        case sf::Event::MouseButtonReleased:
          mouse_down = false;
          if (object_dropped != World::NONE)
            pls_add = true;
          break;
          
        case sf::Event::MouseMoved:
          if (mouse_down && !hovered)
          {
            view_offset_x = view.getCenter().x + mouse_down_x - mouse.x;
            view_offset_y = view.getCenter().y + mouse_down_y - mouse.y;
          }
          break;
          
        case sf::Event::MouseWheelScrolled:
        {
          if (!hovered)
            view.zoom(1 + event.mouseWheelScroll.delta * - 0.03);
        }
      }
    }
  
    // ====================== V === imgui === V ====================== \\
    
    ImGui::SFML::Update(window, deltaClock.restart());
  
    ImGui::ShowDemoWindow();
    
    ImGui::Begin("Control Panel bitches", NULL, ImGuiWindowFlags_MenuBar);
    
    hovered = ImGui::IsWindowHovered();
    
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
  
      if (state == 1)
      {
        if (ImGui::Button("step"))
          world.tick();
      } else
      { ImGui::Text("\tfps: %1.0f", ImGui::GetIO().Framerate); }
  
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
      object_drop_amount = 1;
      object_dropped = World::BLOB;
      ImGui::BeginTooltip();
      ImGui::SetTooltip("1");
      ImGui::EndTooltip();
      ImGui::EndDragDropSource();
    }
    ImGui::SameLine();
  
    ImGui::Button(" 10 blobs ");
    if (ImGui::BeginDragDropSource())
    {
      object_drop_amount = 10;
      object_dropped = World::BLOB;
      ImGui::BeginTooltip();
      ImGui::SetTooltip("10");
      ImGui::EndTooltip();
      ImGui::EndDragDropSource();
    }
    ImGui::SameLine();
  
    ImGui::Button(" 50 blobs ");
    if (ImGui::BeginDragDropSource())
    {
      object_drop_amount = 50;
      object_dropped = World::BLOB;
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
        ImGui::Text("mouse x:\t%i\n\t  y:\t%i", (int)mouse.x, (int)mouse.y);
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
              ImGui::Text("%i", (int) world.blobs[i].logic.pos.x);
              ImGui::TableNextColumn();
              ImGui::Text("%i", (int) world.blobs[i].logic.pos.y);
            }
            ImGui::EndTable();
          }
        }
        ImGui::EndTabItem();
      }
  
      if (ImGui::BeginTabItem("physics"))
      {
        ImGui::Text("approximate collision checks per frame: %i", (int)pow(world.blobs.size(), 2));
        
        if (ImGui::CollapsingHeader("hitboxes"))
        {
          ImGui::Checkbox("blobs", &hitbox_blob);
          ImGui::Checkbox("obstacles", &hitbox_static_objects);
//          ImGui::Checkbox("quadtree", nullptr);
          ImGui::Checkbox("mouse", &hitbox_mouse);
          ImGui::SameLine();
          
          static char *selected;
          if (mouse_hitbox_type == CIRCLE) selected = "circle";
          if (mouse_hitbox_type == LINE) selected = "line";
          if (mouse_hitbox_type == RAY) selected = "ray";
          if (ImGui::BeginCombo("hitbox shape", selected))
          {
            if (ImGui::Selectable("circle"))
              mouse_hitbox_type = CIRCLE;
            
            if (ImGui::Selectable("line"))
              mouse_hitbox_type = LINE;
            
            if (ImGui::Selectable("ray"))
              mouse_hitbox_type = RAY;
            
            ImGui::EndCombo();
          }
        }
        
        ImGui::SliderFloat("stopping threshold", &world.basically_zero, 0.f, 0.01f);
        ImGui::SliderFloat("friction", &world.friction_c, 0.f, 0.4f);
        ImGui::SliderFloat("deflection threshold", &world.activate_deflection_at, 0.f, 10.f);
  
        ImGui::Text("drag and drop:");
        
        ImGui::Button("melon");
        if (ImGui::BeginDragDropSource())
        {
          object_dropped = World::MELON;
          ImGui::BeginTooltip();
          ImGui::SetTooltip("melon");
          ImGui::EndTooltip();
          ImGui::EndDragDropSource();
        }
        
        ImGui::Button("stick");
        if (ImGui::BeginDragDropSource())
        {
          object_dropped = World::STICK;
          ImGui::BeginTooltip();
          ImGui::SetTooltip("stick");
          ImGui::EndTooltip();
          ImGui::EndDragDropSource();
        }
        
        ImGui::Button("ray");
        if (ImGui::BeginDragDropSource())
        {
          object_dropped = World::RAY;
          ImGui::BeginTooltip();
          ImGui::SetTooltip("ray");
          ImGui::EndTooltip();
          ImGui::EndDragDropSource();
        }
  
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
      world.tick();
  
    // logikk
    if (pls_add && object_dropped != World::NONE)
    {
      world.add(object_dropped, mouse.x, mouse.y, object_drop_amount);
      pls_add = false;
      object_dropped = World::NONE;
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
    
    // grafikk
    window.clear();
  
    world.render();
    ImGui::SFML::Render(window);
    
    if (hitbox_mouse)
    {
      static sf::CircleShape circle_gfx;
      static sf::Vertex line_gfx[2];
      static sf::RectangleShape rline_gfx;
      
      switch (mouse_hitbox_type)
      {
        case CIRCLE:
        {
          Ask::Physics::Circle circle(mouse.x, mouse.y, 20);
          if (0)// !Ask::Physics::intersects(circle, world.bounds))
          {
            circle_gfx.setFillColor(hitbox_hit);
            window.draw(fit_to_bounds(circle_gfx, circle));
          }
          else
          {
            for (auto &blob: world.blobs)
            {
              if (Ask::Physics::intersects(circle, blob.graphics.bounds))
              {
                circle_gfx.setFillColor(hitbox_hit);
                break;
              }
              circle_gfx.setFillColor(hitbox_unhit);
            }
            window.draw(fit_to_bounds(circle_gfx, circle));
          }
        } break;
        
        case LINE:
        {
          std::cout << "line\n";
          Ask::Physics::Line line(mouse.x, mouse.y, mouse.x - 100, mouse.y - 100);
          line_gfx[0].color = sf::Color::White;
          line_gfx[1].color = sf::Color::White;
          window.draw(fit_to_bounds(line_gfx, line), 2, sf::Lines);
          line_gfx[0].position.x = 0;
          line_gfx[0].position.y = 0;
          line_gfx[1].position.x = 200;
          line_gfx[1].position.y = 200;


//          circle_gfx.setFillColor(sf::Color::White);
//          circle_gfx.setRadius(100);
//          window.draw(circle_gfx);
        } break;
        
        case RAY:
        {
          static Ask::Physics::Ray ray;
          ray = {(int)mouse.x, (int)mouse.y, 100, 100};
  
          rline_gfx.setFillColor(hitbox_unhit);
          
          for (auto &blob: world.blobs)
          {
            if (Ask::Physics::intersects(ray, blob.graphics.bounds))
            {
              rline_gfx.setFillColor(hitbox_hit);
              break;
            }
          }
          
          window.draw(fit_to_bounds(rline_gfx, ray));
        }
      }
    }
    sf::RectangleShape rect;
    window.display();
  }
  
  ImGui::SFML::Shutdown();
  
  return 0;
}