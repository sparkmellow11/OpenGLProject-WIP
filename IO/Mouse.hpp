//
// Created by schan on 26/12/2025.
//

#pragma once

enum class MouseState
{
    Disabled,
    HiddenLocked,
    Shown
};

struct Mouse
{
    bool firstMove;
    float lastX;
    float lastY;
    bool locked = false;
    bool hidden = true;

    Mouse(bool firstMove, float lastX, float lastY);
};