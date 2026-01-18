//
// Created by schan on 26/12/2025.
//

#include "Rectangle.hpp"

Rectangle::Rectangle(const float horizontalLength, const float verticalLength, const char* path)
{
    vertices[0].Position = {-horizontalLength/2.0f, -verticalLength/2.0f, 0.0f};
    vertices[1].Position = {horizontalLength/2.0f, -verticalLength/2.0f, 0.0f};
    vertices[2].Position = {horizontalLength/2.0f, verticalLength/2.0f, 0.0f};
    vertices[3].Position = {-horizontalLength/2.0f, verticalLength/2.0f, 0.0f};
    for (Vertex& vertex : vertices)
    {
        vertex.Normal = {0,0,1};
    }
    vertices[0].TexCoords = {0.0f, 0.0f};
    vertices[1].TexCoords = {1.0f, 0.0f};
    vertices[2].TexCoords = {1.0f, 1.0f};
    vertices[3].TexCoords = {0.0f, 1.0f};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

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

    texture.id = TextureFromFile(path, PROJECT_ROOT);
    texture.type = "texture_diffuse";
}

void Rectangle::Draw(const Shader& shader) const
{
    glActiveTexture(GL_TEXTURE0); // activate texture unit first
    // retrieve texture number (the N in diffuse_textureN)
    const std::string name = texture.type;
    const std::string number = "1";
    shader.setFloat((name + number).c_str(), 0.0f);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glActiveTexture(GL_TEXTURE0);
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
