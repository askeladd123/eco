//
// Created by askso on 25/06/2022.
//

#ifndef ECO_GUI_H
#define ECO_GUI_H

// standard lib
#include <iostream>
#include <numeric>

// extern lib
//#include "SFML/Graphics.hpp"
//#include "SFML/System.hpp"
//#include "SFML/Window.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include <box2d/box2d.h>

// mine includes
#include "global_var.h"
#include "global_def.h"
#include "game_engine.h"

inline void gui()
{
  ImGui::Begin("Control Panel bitches", NULL, ImGuiWindowFlags_MenuBar);
  
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
        game_engine.tick();
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
    object_dropped = Game_engine::BLOB;
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
    object_dropped = Game_engine::BLOB;
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
    object_dropped = Game_engine::BLOB;
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
      // TODO selecting med menyen
      ImGui::Text("population: %i", game_engine.blobs.size());
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
          
          for (int i = 0; i < game_engine.blobs.size(); i++)
          {
            char label[32];
            sprintf(label, "%s", game_engine.blobs[i].name.c_str());
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            if (ImGui::Selectable(label, selected_blob == i, ImGuiSelectableFlags_SpanAllColumns))
              selected_blob = i;
            
            ImGui::TableNextColumn();
            ImGui::Text("%i", (int) game_engine.blobs[i].logic.body->GetPosition().x);
            ImGui::TableNextColumn();
            ImGui::Text("%i", (int) game_engine.blobs[i].logic.body->GetPosition().y);
          }
          ImGui::EndTable();
        }
      }
      
      ImGui::Separator();
      if (selected_entity != nullptr)
      {
        ImGui::Text("selected item: ");
        ImGui::SameLine();
        if (selected_entity->id == Entity::BLOB)
        {
          ImGui::Text(((Blob*)selected_entity)->name.c_str());
          
          if (!take_control)
          {
            if (ImGui::Button("take control"))
            {
              take_control = true;
              ((Blob *) selected_entity)->mute = true;
            }
          } else
          {
            if (ImGui::Button("stop"))
            {
              take_control = false;
              ((Blob *) selected_entity)->mute = false;
            };
          }
          
          if (ImGui::Button("view neurons"))
          {
            ImGui::OpenPopup("joa");
          }
          
          if (ImGui::BeginPopup("joa"))
          {
            ImGui::Text("neural network");
            ImGui::Image(game_engine.blobs[0].brain.render());
            ImGui::EndPopup();
          }
        }
      }
      else
        ImGui::Text("right-click an item to select it");
      
      ImGui::EndTabItem();
    }
    
    if (ImGui::BeginTabItem("physics"))
    {
      ImGui::Text("approximate collision checks per frame: %i", (int)pow(game_engine.blobs.size(), 2));
      
      if (ImGui::CollapsingHeader("hitboxes"))
      {
        ImGui::Checkbox("blobs", &hitbox_blob);
        ImGui::Checkbox("obstacles", &hitbox_static_objects);
//          ImGui::Checkbox("quadtree", nullptr);
        ImGui::Checkbox("mouse", &hitbox_mouse);
        ImGui::SameLine();
        
        static std::string selected;
        if (mouse_hitbox_type == CIRCLE) selected = "circle";
        if (mouse_hitbox_type == LINE) selected = "line";
        if (mouse_hitbox_type == RAY) selected = "ray";
        if (ImGui::BeginCombo("hitbox shape", selected.c_str()))
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

//        ImGui::SliderFloat("stopping threshold", &game_engine.basically_zero, 0.f, 0.01f);
//        ImGui::SliderFloat("friction", &game_engine.friction_c, 0.f, 0.4f);
//        ImGui::SliderFloat("deflection threshold", &game_engine.activate_deflection_at, 0.f, 10.f);
      
      ImGui::Text("drag and drop:");
      
      ImGui::Button("melon");
      if (ImGui::BeginDragDropSource())
      {
        object_dropped = Game_engine::MELON;
        ImGui::BeginTooltip();
        ImGui::SetTooltip("melon");
        ImGui::EndTooltip();
        ImGui::EndDragDropSource();
      }
      
      ImGui::Button("stick");
      if (ImGui::BeginDragDropSource())
      {
        object_dropped = Game_engine::STICK;
        ImGui::BeginTooltip();
        ImGui::SetTooltip("stick");
        ImGui::EndTooltip();
        ImGui::EndDragDropSource();
      }
      
      ImGui::Button("ray");
      if (ImGui::BeginDragDropSource())
      {
        object_dropped = Game_engine::RAY;
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
}

#endif //ECO_GUI_H
