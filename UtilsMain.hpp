//
// Created by schan on 17/01/2026.
//

#pragma once

#include "Render/Shader.hpp"
#include "Render/Model.hpp"
#include "Render/Rectangle.hpp"
#include "IO/Window.hpp"
#include "ImGuiThing.hpp"
#include "stb_image.h"

#include "Utils.hpp"
#include "Render/UISystem.hpp"


inline void LoadModels(std::vector<Model>& models)
{
    stbi_set_flip_vertically_on_load(true);
    models.emplace_back((projectRoot + "/images/slime/simpleslime.obj").c_str());
    models.emplace_back((projectRoot + "/images/nahobino/smt_v_protagonist_nahobino_ver_dl_rip__blend_by_emilyblend34_deuihsp.obj").c_str());
}

inline void DrawFloor(Shader& shader, const Rectangle& tile, const float sideLength)
{
    for (int i = 0; i < (int)sideLength; i++)
    {
        for (int j = 0; j < (int)sideLength; j++)
        {
            shader.setModelMatrix({-sideLength/2.0f + (float)i, -1.0f, -sideLength/2.0f + (float)j}, ones3, glm::half_pi<float>(), unitX);
            tile.Draw(shader);
        }
    }
}