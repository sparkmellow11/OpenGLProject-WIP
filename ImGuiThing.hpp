//
// Created by schan on 27/12/2025.
//

#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <vector>
#include "IO/Window.hpp"

namespace ImGuiThing
{
    void Init(const Window& window);

    void ShowModelMoveWindow(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& rotations);

    void Render();

    void Terminate();
}