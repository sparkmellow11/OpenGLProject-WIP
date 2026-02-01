//
// Created by schan on 10/09/2025.
//
#include "Mesh.hpp"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures) :
vertices(vertices), indices(indices), textures(textures)
{
    setupMesh();
}

void Mesh::Draw(const Shader& shader) const
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate texture unit first
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name;
        if (textures[i].type == TextureType::Diffuse)
        {
            name = "texture_diffuse";
            number = std::to_string(diffuseNr++);
        }
        else if (textures[i].type == TextureType::Specular)
        {
            name = "texture_specular";
            number = std::to_string(specularNr++);
        }
        shader.setFloat((name + number).c_str(), (float)i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, (int)vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (int)indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

    //position attrib
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
    //normal attrib
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)offsetof(Vertex, Normal));
    //texture attrib
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}
