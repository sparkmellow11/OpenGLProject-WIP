//
// Created by schan on 17/01/2026.
//

#include "UISystem.hpp"

void UISystem::Init(const Camera& camera)
{
    screenRight = -camera.GetLeftDirection();
    screenUp = camera.GetScreenUpDirection();
    initialModelMatrix = glm::mat4(1.0f);
    initialModelMatrix = glm::translate(initialModelMatrix, camera.position);
    initialModelMatrix = glm::rotate(initialModelMatrix, camera.colatitude-glm::half_pi<float>(), -screenRight);
    initialModelMatrix = glm::rotate(initialModelMatrix, camera.azimuth-glm::half_pi<float>(), camera.upDirection);
    finalModelMatrix = initialModelMatrix;
}

void UISystem::Translate(const glm::vec2& screenPos)
{
    finalModelMatrix = glm::translate(finalModelMatrix, {screenPos.x, screenPos.y, 0.0f});
}

void UISystem::Scale(const glm::vec2& scale)
{
    finalModelMatrix = glm::scale(finalModelMatrix, {scale, 1.0f});
}

void UISystem::DrawRect(const Shader& shader, const Rectangle& rect)
{
    shader.setMat4("model", glm::value_ptr(finalModelMatrix));
    rect.Draw(shader);
    finalModelMatrix = initialModelMatrix;
}

void UISystem::drawPrototypeUIElements(const Shader& shader, const Rectangle& rect, const glm::vec4 tintColor,
    const int currentElement, const int elementCount,
    const glm::vec2& initialPlacement, const float angle, const float spacing)
{

    const auto timeMod = glm::clamp(timer, 0.0f, 0.3f)/3.0f;
    for (int i = 0; i < elementCount; i++)
    {
        finalModelMatrix = initialModelMatrix;
        Translate(initialPlacement + spacing*static_cast<float>(i) * glm::vec2(glm::cos(angle),glm::sin(angle)));
        if (i == currentElement)
        {
            Scale(ones2 + timeMod);
            shader.setVec4("tintColor", glm::value_ptr(tintColor));
        } else if (std::abs(i - currentElement) == 1)
        {
            Scale(ones2 + timeMod/2.0f);
        }
        Scale({0.6f,0.6f});
        shader.setMat4("model", glm::value_ptr(finalModelMatrix));
        rect.Draw(shader);
        shader.setVec4("tintColor", glm::value_ptr(ones4));
    }
}

void UISystem::drawPrototypeUIElements(const Shader& shader, const Rectangle& rect, const Rectangle& hover,
    const int currentElement, const int elementCount,
    const glm::vec2& initialPlacement, const float angle, const float spacing)
{
    for (int i = 0; i < elementCount; i++)
    {
        finalModelMatrix = initialModelMatrix;
        Translate(initialPlacement + spacing*static_cast<float>(i) * glm::vec2(glm::cos(angle),glm::sin(angle)));
        shader.setMat4("model", glm::value_ptr(finalModelMatrix));
        rect.Draw(shader);
        if (i == currentElement)
        {
            hover.Draw(shader);
        }
    }
}

void UISystem::UpdateTimer(const float deltaTime)
{
    timer += deltaTime;
}

void UISystem::ResetTimer()
{
    timer = 0.0f;
}

void UISystem::SetUIElementPosLine(UIMenu& menu, const glm::vec2& initialPos, const glm::vec2& finalPos)
{
    for (int i = 0; i < menu.elements.size(); i++)
    {
        const auto t = static_cast<float>(i)/static_cast<float>(menu.elements.size());
        menu.elements[i].pos = myLerp<glm::vec2>(initialPos, finalPos, t);
    }
}

void UISystem::SetElementsSame(UIMenu& menu, Rectangle& rect, const int elementCount)
{
    for (int i = 0; i < elementCount; i++)
    {
        menu.elements.emplace_back(rect);
    }
}
