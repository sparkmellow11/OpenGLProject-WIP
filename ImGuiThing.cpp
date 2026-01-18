//
// Created by schan on 27/12/2025.
//

#include "ImGuiThing.hpp"

void ImGuiThing::Init(const Window& window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
}


void ImGuiThing::ShowModelMoveWindow(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& rotations)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    for (int i = 0; i < positions.size(); i++)
    {
        ImGui::PushID(i);
        ImGui::Text("Model no. %d", i);
        ImGui::SliderFloat("x ", &positions[i].x, -10.0f, 10.0f);
        ImGui::SliderFloat("y", &positions[i].y, -10.0f, 10.0f);
        ImGui::SliderFloat("z", &positions[i].z, -10.0f, 10.0f);
        ImGui::SliderFloat("colatitude", &rotations[i].x, 0.0f, glm::pi<float>());
        ImGui::SliderFloat("azimuth", &rotations[i].y, 0.0f, glm::two_pi<float>());
        if (ImGui::Button("Save")) {}
        ImGui::PopID();
    }
}

void ImGuiThing::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiThing::Terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}