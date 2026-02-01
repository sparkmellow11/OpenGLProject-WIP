//
// Created by schan on 17/01/2026.
//

#pragma once

#include "Render/Shader.hpp"
#include "Render/Model.hpp"
#include "Render/Rectangle.hpp"
#include "stb_image.h"

#include "Utils.hpp"
#include "Render2DManager.hpp"


inline void LoadModels(std::vector<Model>& models)
{
    stbi_set_flip_vertically_on_load(true);
    models.emplace_back("/images/slime/simpleslime.obj");
    models.emplace_back("/images/nahobino/smt_v_protagonist_nahobino_ver_dl_rip__blend_by_emilyblend34_deuihsp.obj");
}

inline void DrawFloor(Shader& shader, glm::mat4& modelMatrix, const char* tile, const float sideLength)
{
    for (int i = 0; i < (int)sideLength; i++)
    {
        for (int j = 0; j < (int)sideLength; j++)
        {
            shader.setModelMatrix(modelMatrix, {-sideLength/2.0f + (float)i, -1.0f, -sideLength/2.0f + (float)j}, ones3, glm::half_pi<float>(), -unitX);
            Render2DManager::Draw(shader, tile);
        }
    }
}

inline void LoadRectangles(std::vector<Rectangle>& rectangles)
{
    stbi_set_flip_vertically_on_load(true);
    rectangles.emplace_back("images/whitesquare.png");
    rectangles.emplace_back("images/whitecircle.png");
    rectangles.emplace_back("images/awesomeface.png");
    rectangles.emplace_back("images/container.jpg");
    rectangles.emplace_back("images/minecraft_dirt.png");
    rectangles.emplace_back("images/wall.jpg");

}