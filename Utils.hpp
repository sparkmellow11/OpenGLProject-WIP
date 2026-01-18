//
// Created by schan on 26/12/2025.
//

#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/constants.hpp>

constexpr glm::vec3 unitX(1.0f,0.0f,0.0f);
constexpr glm::vec3 unitY(0.0f,1.0f,0.0f);
constexpr glm::vec3 unitZ(0.0f,0.0f,1.0f);
constexpr glm::vec2 ones2(1.0f);
constexpr glm::vec3 ones3(1.0f);
constexpr glm::vec4 ones4(1.0f);
constexpr glm::mat4 id4(1.0f);
const std::string projectRoot(PROJECT_ROOT);

unsigned int TextureFromFile(const char *path, const std::string &directory);

glm::vec3 GetSphericalDirection(float colatitude, float azimuth);

glm::vec3 GetCameraLeftDirection(float azimuth);

#define DEBUG_LOG(x) std::cerr << #x << " = " << x << std::endl;

float cosTimeDomain(float min, float max, float frequency);

template<typename V>
V myLerp(const V& initial, const V& final, const float t)
{
    assert(t >= 0.0f);
    assert(t <= 1.0f);

    return initial * (1.0f - t) + final * t;
}