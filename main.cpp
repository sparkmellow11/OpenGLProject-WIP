//
// Created by schan on 28/07/2025.
//

#include <filesystem>

#include "Render/Shader.hpp"
#include "Render/Model.hpp"
#include "IO/Window.hpp"
#include "ImGuiThing.hpp"

#include "Utils.hpp"
#include "Render/UISystem.hpp"
#include "UtilsMain.hpp"
#include "imgui/imgui_internal.h"


void initGLSettings()
{
    //enable stuff
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW); // i guess
    glfwSwapInterval(0);
}

/*
void DrawHpBar(const Shader& shader, const Camera& camera, const UIElement& element, const glm::vec3& position, float ratio)
{
    ratio = std::clamp(ratio, 0.0f, 1.0f);

    glDisable(GL_DEPTH_TEST);
    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::half_pi<float>()-camera.colatitude, -camera.GetLeftDirection());
    modelMatrix = glm::rotate(modelMatrix, camera.azimuth-glm::half_pi<float>(), camera.upAxisDirection);
    modelMatrix = glm::scale(modelMatrix, {element.scale,1.0f});
    shader.setMat4("model", glm::value_ptr(modelMatrix));
    auto maxHp = glm::vec4(0.0f,0.0f,0.0f,1.0f);
    shader.setVec4("tintColor", glm::value_ptr(maxHp));
    element.rect->Draw(shader);

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::half_pi<float>()-camera.colatitude, -camera.GetLeftDirection());
    modelMatrix = glm::rotate(modelMatrix, camera.azimuth-glm::half_pi<float>(), camera.upAxisDirection);
    modelMatrix = glm::translate(modelMatrix, -unitX*0.5f*(1.0f-ratio));
    modelMatrix = glm::scale(modelMatrix, {ratio*element.scale.x, element.scale.y,1.0f});
    shader.setMat4("model", glm::value_ptr(modelMatrix));
    auto currHp = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    shader.setVec4("tintColor", glm::value_ptr(currHp));
    element.rect->Draw(shader);
    shader.setVec4("tintColor", glm::value_ptr(ones4));
    glEnable(GL_DEPTH_TEST);
}
*/

int main()
{
    try
    {
        Window window; //trying, if it works then it will be initialised on the outside
    } catch (const std::runtime_error& e)
    {
        std::cerr << "Error in main: " << e.what() << std::endl;
        return -1;
    }
    Window window;

    ImGuiThing::Init(window);

    std::vector<Model> models;
    LoadModels(models);

    const std::string render2dpath = "/images/render2dtextures";
    Render2DManager::addQuads(render2dpath.c_str());

    Shader shader("/Render/shader.vert", "/Render/shader.frag");

    std::vector<glm::vec3> modelPositions(models.size());
    std::vector<glm::vec2> modelRotations(models.size());

    auto& mouse = Window::mouse;
    auto& camera = window.camera;


    //SET DEFAULTS FOR UNIFORMS
    shader.use();
    shader.setVec4("tintColor", glm::value_ptr(ones4));

    UISystem::Init(camera);


    constexpr int mainElementCount = 4;
    LinearButtonArray<mainElementCount> combatMain;
    {
        UISystem::SetElementsSame(combatMain, "container");
        glm::vec2 scale = {2.0f, 1.0f};
        UISystem::SetScale(combatMain, scale);
        glm::vec2 initialPos = {-4.5f, -2.0f};
        glm::vec2 finalPos = {4.5f, -2.0f};
        UISystem::SetUIElementPosLine(combatMain, initialPos, finalPos);
    }

    constexpr int abilityCount = 8;
    LinearButtonArray<abilityCount> combatSkills;
    {
        UISystem::SetElementsSame(combatSkills, "container");
        glm::vec2 scale = {2.0f, 0.75f};
        UISystem::SetScale(combatSkills, scale);
        glm::vec2 initialPos = {-4.5f, 3.0f};
        glm::vec2 finalPos = {-4.5f, -4.0f};
        UISystem::SetUIElementPosLine(combatSkills, initialPos, finalPos);
    }


    glm::mat4 modelMatrix;
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    initGLSettings();

    //Rendering loop ---------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window()))
    {
        window.UpdateDeltaTime();
        window.FPSCounterTitle();

        if (mouse.enabled)
        {
            ImGuiThing::ShowModelMoveWindow(modelPositions, modelRotations);
        }

        UpdateFallingPhysics(camera.position, camera.velocity, window.deltaTime);
        window.processInput();
        if (window.combatUIStart)
        {
            camera.locked = true;
        } else
        {
            camera.locked = false;
            window.processMovementInput();
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //3D ZONE------------------------------------------------------
        glEnable(GL_DEPTH_TEST);
        shader.use();

        projectionMatrix = glm::perspective(glm::radians(camera.GetFOV()), static_cast<float>(Window::WIDTH)/Window::HEIGHT, 0.1f, 100.0f);
        viewMatrix = camera.GetViewMatrix1stPerson();

        shader.setMat4("projection", glm::value_ptr(projectionMatrix));
        shader.setMat4("view", glm::value_ptr(viewMatrix));

        for (int i = 0; i < models.size(); i++)
        {
            shader.setModelMatrix(modelMatrix, modelPositions[i], ones3, modelRotations[i].x, modelRotations[i].y);
            models[i].Draw(shader);
            /*
            UIElement whiterect(rectangles[0]);
            whiterect.scale = {1.0f, 0.1f};
            DrawHpBar(shader, camera, whiterect, modelPositions[i] + unitY, 0.5f);
            */
        }

        shader.setModelMatrix(modelMatrix, {-7.0f, 0.0f, -3.0f}, ones3);
        Render2DManager::Draw(shader, Render2DManager::GetRender2D("container"));

        shader.setModelMatrix(modelMatrix, {-3.0f, -1.0f, -5.0f}, ones3);
        Render2DManager::Draw(shader, Render2DManager::GetRender2D("minecraft_dirt"));

        //drawing the floor
        float sideLength = 20.0f;
        DrawFloor(shader, modelMatrix, "wall", sideLength);

        //2D ZONE-------------------------------------------------
        glDisable(GL_DEPTH_TEST);
        shader.setOrthoProjMatrix(projectionMatrix, Window::halfWidth/100.0f, Window::halfHeight/100.0f);

        UISystem::Init(camera);

        if (window.combatUIStart)
        {
            UISystem::CombatUI(window, shader, combatMain, combatSkills);
        } else
        {
            UISystem::Translate({-5.0f, -2.5f});
            UISystem::DrawRender2D(shader, "whitecircle");

            UISystem::Translate({-5.8f, 3.0f});
            UISystem::DrawRender2D(shader, "awesomeface");
        }


        //imgui thingy
        if (mouse.enabled)
        {
            ImGuiThing::Render();
        }

        //swap buffers
        glfwSwapBuffers(window());
        glfwPollEvents();
    }

    ImGuiThing::Terminate();
    return 0;
}
