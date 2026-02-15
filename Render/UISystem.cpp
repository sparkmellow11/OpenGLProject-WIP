//
// Created by schan on 17/01/2026.
//

#include "UISystem.hpp"

void UISystem::Init(const Camera& camera)
{
    initialModelMatrix = glm::mat4(1.0f);
    initialModelMatrix = glm::translate(initialModelMatrix, camera.position);
    initialModelMatrix = glm::rotate(initialModelMatrix, camera.colatitude-glm::half_pi<float>(), -camera.screenRight);
    initialModelMatrix = glm::rotate(initialModelMatrix, camera.azimuth-glm::half_pi<float>(), camera.upAxisDirection);
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

void UISystem::DrawRender2D(const Shader& shader, const Render2D& render)
{
    shader.setMat4("model", glm::value_ptr(finalModelMatrix));
    Render2DManager::Draw(shader, render);
    finalModelMatrix = initialModelMatrix;
}

void UISystem::DrawRender2D(const Shader& shader, const char* name)
{
    shader.setMat4("model", glm::value_ptr(finalModelMatrix));
    Render2DManager::Draw(shader, name);
    finalModelMatrix = initialModelMatrix;
}


void UISystem::UpdateTimer(const float deltaTime)
{
    timer += deltaTime;
}

void UISystem::ResetTimer()
{
    timer = 0.0f;
}

