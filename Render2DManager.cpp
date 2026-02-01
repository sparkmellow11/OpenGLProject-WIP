//
// Created by schan on 28/01/2026.
//

#include "Render2DManager.hpp"

#include <filesystem>


void Render2DManager::Draw(const Shader& shader, const Render2D& render)
{
    glActiveTexture(GL_TEXTURE0 ); // activate texture unit first
    // retrieve texture number (the N in diffuse_textureN)
    std::string name;
    if (render.texture.type == TextureType::Diffuse)
    {
        name = "texture_diffuse";
    } else if (render.texture.type == TextureType::Specular)
    {
        name = "texture_specular";
    }
    shader.setFloat(name, 0);
    glBindTexture(GL_TEXTURE_2D, render.texture.id);
    glActiveTexture(GL_TEXTURE0);
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, GLM_COUNTOF(indices), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Render2DManager::Draw(const Shader& shader, const char* name)
{
    Draw(shader, GetRender2D(name));
}

Render2D& Render2DManager::GetRender2D(const char* name)
{
    assert(renders.count(name) && "No such key exists in the render2d map.");
    return renders[name];
}

Render2D Render2DManager::setupQuad(const char* path)
{
    Render2D render;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, GLM_COUNTOF(vertices) * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLM_COUNTOF(indices) * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

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

    render.texture.path = path;
    render.texture.id = TextureFromFile(render.texture.path.c_str(), PROJECT_ROOT);
    render.texture.type = TextureType::Diffuse;
    return render;
}

/*
void Render2DManager::addQuad(const char* path)
{
    renders[std::string(path).substr(std::string(path).find_last_of('/'), std::string(path).find_last_of('.'))] = setupQuad(path);
}

void Render2DManager::addQuads(const std::vector<const char*>& paths)
{
    for (const auto path : paths)
    {
        renders[std::string(path).substr(std::string(path).find_last_of('/'), std::string(path).find_last_of('.'))] = setupQuad(path);
    }
}
*/

void Render2DManager::addQuads(const char* directory)
{
    for (const auto& entry : std::filesystem::directory_iterator(projectRoot + directory)) {
        if (std::filesystem::is_regular_file(entry.status())) {
            std::filesystem::path relative_path = std::filesystem::relative(entry.path(), projectRoot);
            std::string path = relative_path.generic_string();
            const int start = path.find_last_of('/')+1;
            std::string name = path.substr(start, path.size()-start-4);
            renders[name] = setupQuad(path.c_str());
        }
    }
}
