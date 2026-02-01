//
// Created by schan on 24/08/2025.
//

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Utils.hpp"

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const ::std::string& name, const float *matrix) const;
    void setVec4(const std::string& name, const float* vec) const;

    void setModelMatrix(glm::mat4& modelMatrix, const glm::vec3& translation, const glm::vec3& scaling,
                            float rotation, const glm::vec3& rotationAxis) const;

    void setModelMatrix(glm::mat4& modelMatrix, const glm::vec3& translation, const glm::vec3& scaling) const;

    void setModelMatrix(glm::mat4& modelMatrix, const glm::vec3& translation, const glm::vec3& scaling,
                        float colatitude, float azimuth) const;

    void setOrthoProjMatrix(glm::mat4& projectionMatrix, float halfWidth, float halfHeight) const;

    void setPerspProjMatrix(glm::mat4& projectionMatrix, float fov, float width, float height) const;

    void setViewMatrix(const glm::mat4& viewMatrix) const;
};
