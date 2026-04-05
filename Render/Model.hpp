//
// Created by schan on 10/09/2025.
//

#pragma once
#include "Mesh.hpp"
#include "../Utils.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model
{
public:
    Model() = default;
    explicit Model(const char* path);
    void Draw(const Shader &shader) const;
private:
    // model data
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    void loadModel(const std::string& path);
    void processNode(const aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(const aiMaterial *mat, aiTextureType type, const std::string& typeName);
};

unsigned int TextureFromFile(const char *path, const std::string &directory);