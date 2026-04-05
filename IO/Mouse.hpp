//
// Created by schan on 26/12/2025.
//

#pragma once

struct Mouse
{
    bool firstMove;
    float lastX;
    float lastY;
    bool enabled = false;

    Mouse(bool firstMove, float lastX, float lastY);
};