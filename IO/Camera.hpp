//
// Created by schan on 29/08/2025.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Utils.hpp"

class Camera {
public:
    Camera(glm::vec3 cameraPos, glm::vec3 cameraDirection, float sensitivity);

    void UpdateCamera(glm::vec2 mouseOffset);

    void ModifyCameraPos(glm::vec3 displacement);

    void ModifyCameraFOV(float deltaFov);

    [[nodiscard]] glm::mat4 GetViewMatrix1stPerson() const;

    [[nodiscard]] glm::mat4 GetViewMatrix3rdPerson(glm::vec3 target, float distance) const;

    [[nodiscard]] glm::vec3 GetPosition() const;

    [[nodiscard]] glm::vec3 GetFacingDirection() const;

    [[nodiscard]] glm::vec3 GetUpDirection() const;

    [[nodiscard]] float GetFOV() const;

    [[nodiscard]] glm::vec3 GetPlaneFacingDirection() const;

    [[nodiscard]] glm::vec3 GetLeftDirection() const;

    [[nodiscard]] glm::vec3 GetScreenUpDirection() const;

    void UpdateFallingPhysics(glm::vec3& position, glm::vec3& velocity, float deltaTime);

//private:
    float colatitude;
    float azimuth;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 facingDirection;
    glm::vec3 upDirection;
    float sensitivity;
    float fov;
    float speed;

};
