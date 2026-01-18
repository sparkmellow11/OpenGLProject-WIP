//
// Created by schan on 10/09/2025.
//

#pragma once
#include <string>
#include <vector>
#include <glm/vec3.hpp>

#include "Shader.hpp"


struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};


class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
    void Draw(const Shader &shader) const;

private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();

};
