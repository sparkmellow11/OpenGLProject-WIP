//
// Created by schan on 17/01/2026.
//

#pragma once

#include "../IO/Camera.hpp"
#include "Shader.hpp"
#include "Rectangle.hpp"
#include "../Utils.hpp"

struct UIElement
{
    Rectangle* rect;
    glm::vec2 pos;
    float rotation;
    explicit UIElement(Rectangle& rect) : rect(&rect) {}
};

struct UIMenu
{
    std::vector<UIElement> elements;
    int currentElement = 0;
    float timer = 0.0f;
    UIMenu() = default;
    explicit UIMenu(const std::vector<UIElement>& elements) : elements(elements) {}
};

struct UISystem
{
    static void Init(const Camera& camera);

    static void Translate(const glm::vec2& screenPos);

    static void Scale(const glm::vec2& scale);

    static void DrawRect(const Shader& shader, const Rectangle& rect);

    static void drawPrototypeUIElements(const Shader& shader, const Rectangle& rect, glm::vec4 tintColor,
        int currentElement, int elementCount,
        const glm::vec2& initialPlacement, float angle, float spacing);

    static void drawPrototypeUIElements(const Shader& shader, const Rectangle& rect, const Rectangle& hover,
        int currentElement, int elementCount,
        const glm::vec2& initialPlacement, float angle, float spacing);

    static void UpdateTimer(float deltaTime);

    static void ResetTimer();

    static void SetUIElementsLine (const glm::vec2& initialPos, float lineAngle, float spacing, float rotation);
    static void SetUIElementPosLine (UIMenu& menu, const glm::vec2& initialPos, const glm::vec2& finalPos);

    static void SetElementsSame(UIMenu& menu, Rectangle& rect, int elementCount);

private:
    static inline glm::mat4 initialModelMatrix;
    static inline glm::mat4 finalModelMatrix;
    static inline glm::vec3 screenRight;
    static inline glm::vec3 screenUp;
    static inline float timer = 0.0f;

};