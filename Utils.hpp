//
// Created by schan on 26/12/2025.
//

#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

constexpr glm::vec3 unitX(1.0f,0.0f,0.0f);
constexpr glm::vec3 unitY(0.0f,1.0f,0.0f);
constexpr glm::vec3 unitZ(0.0f,0.0f,1.0f);
constexpr glm::vec2 ones2(1.0f);
constexpr glm::vec3 ones3(1.0f);
constexpr glm::vec4 ones4(1.0f);
constexpr glm::mat4 id4(1.0f);
const std::string projectRoot(PROJECT_ROOT);

#define DEBUG_LOG(x) std::cerr << #x << " = " << x << std::endl;
#define GET_VARIABLE_NAME(Variable) (#Variable)


unsigned int TextureFromFile(const char *path, const std::string &directory);

glm::vec3 GetSphericalDirection(float colatitude, float azimuth);

glm::vec3 GetCameraLeftDirection(float azimuth);

float cosTimeDomain(float min, float max, float frequency, float time);

void UpdateFallingPhysics(glm::vec3& position, glm::vec3& velocity, float deltaTime);

/*
template <typename T, T min, T max>
struct RestrictedNumber
{
    T set(T value) {}
    T get() {return number;}
private:
    T number;
};
*/

template<typename V>
V myLerp(const V& initial, const V& final, const float t)
{
    assert(t >= 0.0f && "t is negative");
    assert(t <= 1.0f && "t is > 1");

    return initial * (1.0f - t) + final * t;
}