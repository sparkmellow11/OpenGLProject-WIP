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
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window(), true);
    ImGui_ImplOpenGL3_Init();
}



void ImGuiThing::ShowModelMoveWindow(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& rotations)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    std::string itemStrs[positions.size()];
    const char* items[positions.size()];
    for (int i = 0; i < IM_ARRAYSIZE(items); i++)
    {
        itemStrs[i] = "Model no. " + std::to_string(i+1);
        items[i] = itemStrs[i].c_str();
    }
    static int currentIndex = 0;
    ImGui::Combo("##Modelrepositioning", &currentIndex, items, IM_ARRAYSIZE(items));
    constexpr float minmax = 5.0f;
    ImGui::SliderFloat("x ", &positions[currentIndex].x, -minmax, minmax);
    ImGui::SliderFloat("y", &positions[currentIndex].y, -minmax, minmax);
    ImGui::SliderFloat("z", &positions[currentIndex].z, -minmax, minmax);
    ImGui::SliderFloat("colatitude", &rotations[currentIndex].x, 0.0f, glm::two_pi<float>());
    ImGui::SliderFloat("azimuth", &rotations[currentIndex].y, 0.0f, glm::two_pi<float>());
    if (ImGui::Button("Save")) {}
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