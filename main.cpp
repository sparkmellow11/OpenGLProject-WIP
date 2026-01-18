//
// Created by schan on 28/07/2025.
//

#include <filesystem>

#include "Render/Shader.hpp"
#include "Render/Model.hpp"
#include "Render/Rectangle.hpp"
#include "IO/Window.hpp"
#include "ImGuiThing.hpp"

#include "Utils.hpp"
#include "Render/UISystem.hpp"
#include "UtilsMain.hpp"



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

    Rectangle smiley(1.0f,1.0f,"images/awesomeface.png");
    Rectangle container(1.0f,3.0f,"images/container.jpg");
    Rectangle container2(2.0f,1.0f,"images/container.jpg");
    Rectangle mcdirt(1.0f,1.0f,"images/minecraft_dirt.png");
    Rectangle wall(1.0f, 1.0f, "images/wall.jpg");
    Rectangle whitecircle(2.0f,2.0f,"images/2dcircle/diffuse.png");

    std::cerr << "Wawaweewa" << std::endl;
    Shader shader((projectRoot + "/Render/shader.vert").c_str(), (projectRoot + "/Render/shader.frag").c_str());
    std::cerr << "Wawaweewa" << std::endl;


    std::vector<glm::vec3> modelPositions(models.size());
    std::vector<glm::vec2> modelRotations(models.size());

    auto& mouse = Window::mouse;
    auto& camera = window.camera;


    //SET DEFAULTS FOR UNIFORMS AFTER THIS
    shader.use();
    shader.setVec4("tintColor", glm::value_ptr(ones4));

    //enable stuff
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //Rendering loop ---------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window()))
    {
        if (!mouse.locked && !mouse.hidden)
        {
            ImGuiThing::ShowModelMoveWindow(modelPositions, modelRotations);
        }

        window.UpdateDeltaTime();
        camera.UpdateFallingPhysics(camera.position, camera.velocity, window.deltaTime);
        window.processInput();
        if (!window.combatUIStart)
        {
            mouse.locked = false;
            window.processMovementInput();
        } else
        {
            mouse.locked = true;
        }


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //3D ZONE------------------------------------------------------
        glEnable(GL_DEPTH_TEST);
        shader.setPerspProjMatrix(camera.GetFOV(), Window::WIDTH, Window::HEIGHT);
        shader.setViewMatrix(camera.GetViewMatrix1stPerson());

        for (int i = 0; i < models.size(); i++)
        {
            auto colatitude = modelRotations[i].x;
            auto azimuth = modelRotations[i].y;
            shader.setModelMatrix(modelPositions[i], ones3, colatitude, azimuth);
            models[i].Draw(shader);
        }

        shader.setModelMatrix({-7.0f, 0.0f, -3.0f}, ones3);
        container.Draw(shader);

        shader.setModelMatrix({-3.0f, -1.0f, -5.0f}, ones3);
        mcdirt.Draw(shader);

        //drawing the floor
        float sideLength = 20.0f;
        DrawFloor(shader, wall, sideLength);

        //2D ZONE-------------------------------------------------
        glDisable(GL_DEPTH_TEST);
        shader.setOrthoProjMatrix(Window::halfWidth/100.0f, Window::halfHeight/100.0f);

        UISystem::Init(camera);

        UIMenu combatMain;
        constexpr int mainElementCount = 4;
        UISystem::SetElementsSame(combatMain, container2, mainElementCount);
        constexpr glm::vec2 combatMainPosIni = {-4.5f, -2.0f};
        constexpr glm::vec2 combatMainPosFin = {4.5f, -2.0f};
        UISystem::SetUIElementPosLine(combatMain, combatMainPosIni, combatMainPosFin);

        UIMenu combatSkills;
        constexpr int abilityCount = 8;
        UISystem::SetElementsSame(combatSkills, container, abilityCount);
        constexpr glm::vec2 combatSkillsPosIni = {-4.5f, 2.0f};
        constexpr glm::vec2 combatSkillsPosFin = {-4.5f, -2.0f};
        UISystem::SetUIElementPosLine(combatSkills, combatSkillsPosIni, combatSkillsPosFin);

        if (window.combatUIStart)
        {
            if (window.combatUIMain)
            {
                combatMain.currentElement = window.processCombatUIInput(window(), combatMain.currentElement, mainElementCount);
                UISystem::


                if (window.positiveEdgeCheck(window(), GLFW_KEY_ENTER))
                {
                    smiley.Draw(shader);
                    window.combatUIMain = false;
                    switch (window.currentUIElement)
                    {
                    case 0:
                        window.combatUISkills = true;
                        break;
                    default:
                        window.combatUIStart = false;
                    }
                }
            } else if (window.combatUISkills)
            {

                auto prevElement = window.currentUIElement;
                window.currentUIElement = std::clamp(window.currentUIElement, 0, abilityCount);
                window.currentUIElement = window.processCombatUIInput(window(), window.currentUIElement, abilityCount);
                if (window.currentUIElement != prevElement) {UISystem::ResetTimer();}
                float frequency = 1.0f;
                float timeMod = cosTimeDomain(0.0f,1.0f,frequency);
                auto rgbMult = ones3;
                auto netColorMult = glm::vec4(rgbMult+timeMod, 1.0f);
                UISystem::UpdateTimer(window.deltaTime);
                UISystem::drawPrototypeUIElements(shader, container2, netColorMult, window.currentUIElement, abilityCount, {-5.0f, 3.0f}, -glm::half_pi<float>(), 0.75f);

                if (window.positiveEdgeCheck(window(), GLFW_KEY_ENTER))
                {
                    window.combatUISkills = false;
                    window.combatUIActionComplete = true;
                    //use demon.skills[currentUIElement]
                }
            } else if (window.combatUIActionComplete)
            {
                window.combatUIActionComplete = false;
                window.combatUIStart = false;
            }


        } else
        {
            UISystem::Translate({-5.0f, -2.5f});
            UISystem::DrawRect(shader, whitecircle);

            UISystem::Translate({-5.8f, 3.0f});
            UISystem::DrawRect(shader, smiley);
        }


        //imgui thingy
        if (!mouse.locked && !mouse.hidden) {ImGuiThing::Render();}

        //swap buffers
        glfwSwapBuffers(window());
        glfwPollEvents();
    }

    ImGuiThing::Terminate();
    return 0;
}
