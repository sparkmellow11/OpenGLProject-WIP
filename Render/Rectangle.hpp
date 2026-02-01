//
// Created by schan on 26/12/2025.
//

#pragma once

#include "Mesh.hpp"
#include "../IO/Camera.hpp"

struct Rectangle
{
    Vertex vertices[4];
    Texture texture;
    unsigned int indices[6] = {0,1,2,2,3,0};
    unsigned int VAO, VBO, EBO;

    explicit Rectangle(const char* path);
    Rectangle(float horizontalLength, float verticalLength, const char* path);

    void Draw(const Shader& shader) const;

};
