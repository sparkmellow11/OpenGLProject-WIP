//
// Created by schan on 17/01/2026.
//

#pragma once

#include "../IO/Camera.hpp"
#include "Shader.hpp"
#include "Rectangle.hpp"
#include "../Utils.hpp"
#include "../Render2DManager.hpp"
#include "../IO/Window.hpp"


struct Transform3D
{
    glm::vec3 scale;
    glm::vec3 position;
    glm::vec2 rotation;
};

struct Transform2D
{
    glm::vec2 scale;
    glm::vec2 position;
    float rotation;
};

struct Motion2D
{
    glm::vec2 velocity;
    glm::vec2 acceleration;
};

struct Motion3D
{
    glm::vec3 velocity;
    glm::vec3 acceleration;
};


template <size_t N>
struct LinearButtonArray
{
    std::array<Transform2D, N> transforms;
    std::array<Render2D, N> renders;
    Transform2D* parent;
};

struct UISystem
{
    static void Init(const Camera& camera);

    static void Translate(const glm::vec2& screenPos);

    static void Scale(const glm::vec2& scale);

    static void DrawRect(const Shader& shader, const Rectangle& rect);

    static void DrawRender2D(const Shader& shader, const Render2D& render);
    static void DrawRender2D(const Shader& shader, const char* name);

    static void UpdateTimer(float deltaTime);

    static void ResetTimer();

    template <size_t N>
    static void SetUIElementPosLine(LinearButtonArray<N>& buttonArray, const glm::vec2& initialPos, const glm::vec2& finalPos)
    {
        for (int i = 0; i < N; i++)
        {
            const auto t = static_cast<float>(i)/static_cast<float>(N);
            buttonArray.transforms[i].position = myLerp<glm::vec2>(initialPos, finalPos, t);
        }
    }

    template <size_t N>
        static void SetScale(LinearButtonArray<N>& buttonArray, const glm::vec2& scale)
    {
        for (int i = 0; i < N; i++)
        {
            buttonArray.transforms[i].scale = scale;
        }
    }

    template <size_t N>
    static void SetElementsSame(LinearButtonArray<N>& buttonArray, Render2D& render)
    {
        for (int i = 0; i < N; i++)
        {
            buttonArray.renders[i] = render;
        }
    }

    template <size_t N>
    static void SetElementsSame(LinearButtonArray<N>& buttonArray, const char* name)
    {
        for (int i = 0; i < N; i++)
        {
            buttonArray.renders[i] = Render2DManager::GetRender2D(name);
        }
    }

    template <size_t N>
    static void DrawAllButtonElements(const Shader& shader, const LinearButtonArray<N>& buttonArray, const glm::vec4& tintColor, const int currentElement)
    {
        assert(currentElement < N && "Current element is larger than buttonArray size.");
        for (int i = 0; i < N; i++)
        {
            finalModelMatrix = initialModelMatrix;
            Translate(buttonArray.transforms[i].position);
            if (i == currentElement)
            {
                Scale(ones2 + 0.1f);
                shader.setVec4("tintColor", glm::value_ptr(tintColor));
            }
            Scale(buttonArray.transforms[i].scale);
            shader.setMat4("model", glm::value_ptr(finalModelMatrix));
            DrawRender2D(shader, buttonArray.renders[i]);
            shader.setVec4("tintColor", glm::value_ptr(ones4));
        }
    }

    template <size_t N, size_t M>
    static void CombatUI(Window& window, const Shader& shader, LinearButtonArray<N>& combatMain, LinearButtonArray<M>& combatSkills)
    {
        auto colour = glm::vec4(2.0f);
        if (window.combatUIMain)
        {
            static int currentElement = 0;
            currentElement = window.processCombatUIInput(window(), currentElement, N);
            UISystem::DrawAllButtonElements(shader, combatMain, colour, currentElement);

            if (window.positiveEdgeCheck(window(), GLFW_KEY_ENTER))
            {
                window.combatUIMain = false;
                switch (currentElement)
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
            static int currentElement = 0;
            currentElement = window.processCombatUIInput(window(), currentElement, M);
            UISystem::DrawAllButtonElements(shader, combatSkills, colour, currentElement);

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
    }

private:
    static inline glm::mat4 initialModelMatrix;
    static inline glm::mat4 finalModelMatrix;
    static inline glm::vec3 screenRight;
    static inline glm::vec3 screenUp;
    static inline float timer = 0.0f;

};