//
// Created by schan on 29/08/2025.
//

#include "Camera.hpp"

Camera::Camera(const glm::vec3 cameraPos, const glm::vec3 cameraDirection, const float sensitivity)
    : colatitude(glm::half_pi<float>()),
    azimuth(glm::half_pi<float>()),
    position(cameraPos),
    velocity(),
    facingDirection(cameraDirection),
    upAxisDirection(glm::vec3(0.0f, 1.0f, 0.0f)),
    sensitivity(sensitivity),
    fov(45.0f)
{
}

void Camera::UpdateCamera(glm::vec2 mouseOffset)
{
    mouseOffset *= 0.01; //just getting proportionalish to degrees
    mouseOffset *= sensitivity;
    azimuth -= mouseOffset.x; //adding goes anticlockwise, hence mouse right would be look left, so use negative
    colatitude -= mouseOffset.y; //adding goes downwards, hence mouse up would be look down, so use negative
    colatitude = glm::clamp(colatitude, 0.1f, glm::pi<float>()-0.1f);
    facingDirection = GetSphericalDirection(colatitude, azimuth);
}

void Camera::ModifyCameraPos(const glm::vec3 displacement)
{
    position += displacement;
}

void Camera::ModifyCameraFOV(const float deltaFov)
{
    fov += deltaFov;
    fov = glm::clamp(fov, 1.0f, 90.0f);
}

glm::mat4 Camera::GetViewMatrix1stPerson() const
{
    return glm::lookAt(position, position + facingDirection, upAxisDirection);
}

glm::mat4 Camera::GetViewMatrix3rdPerson(const glm::vec3 target, const float distance) const
{
    return glm::lookAt(target - distance*facingDirection, target, upAxisDirection);
}

glm::vec3 Camera::GetPosition() const
{
    return position;
}

glm::vec3 Camera::GetFacingDirection() const
{
    return facingDirection;
}

glm::vec3 Camera::GetUpDirection() const
{
    return upAxisDirection;
}

float Camera::GetFOV() const
{
    return fov;
}

glm::vec3 Camera::GetPlaneFacingDirection() const
{
    return {glm::cos(azimuth), 0.0f, -glm::sin(azimuth)};
}

glm::vec3 Camera::GetLeftDirection() const
{
    return {-glm::sin(azimuth), 0.0f, -glm::cos(azimuth)};
}

glm::vec3 Camera::GetScreenUpDirection() const
{
    return glm::cross(facingDirection, GetLeftDirection());
}