//
// Created by schan on 28/01/2026.
//

#pragma once

#include <unordered_map>
#include "Render/Mesh.hpp"
#include "Utils.hpp"

struct Render2D
{
    Texture texture;
    glm::vec4 tint = glm::vec4(1.0f);
};


struct Render2DManager
{
    static Render2D setupQuad(const char* path);

    //static void addQuad(const char* path);
    //static void addQuads(const std::vector<const char*>& paths);
    static void addQuads(const char* directory);

    static void Draw(const Shader& shader, const Render2D& render);

    static void Draw(const Shader& shader, const char* name);

    static Render2D& GetRender2D(const char* name);

private:
    static inline Vertex vertices[4] = {
        {{-0.5f, -0.5f, 0.0f},{0,0,1},{0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f},{0,0,1},{1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f},{0,0,1},{1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f},{0,0,1},{0.0f, 1.0f}}
    };
    static inline int indices[6] = {0,1,2,2,3,0};
    static inline unsigned int VAO, VBO, EBO;
    static inline std::unordered_map<std::string, Render2D> renders;
};