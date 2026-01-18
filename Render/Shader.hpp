//
// Created by schan on 24/08/2025.
//

#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    void setModelMatrix(const glm::vec3& translation, const glm::vec3& scaling,
                        float rotation, const glm::vec3& rotationAxis);

    void setModelMatrix(const glm::vec3& translation, const glm::vec3& scaling);

    void setModelMatrix(const glm::vec3& translation, const glm::vec3& scaling,
                        float colatitude, float azimuth);

    void setOrthoProjMatrix(float halfWidth, float halfHeight);

    void setPerspProjMatrix(float fov, float width, float height);

    void setViewMatrix(const glm::mat4& viewMatrix) const;
};
