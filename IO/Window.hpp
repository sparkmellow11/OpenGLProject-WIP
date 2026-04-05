//
// Created by schan on 26/12/2025.
//

#pragma once

#include <array>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "Mouse.hpp"

struct KeyboardKey
{
    GLint key;
    bool wasPressed = false;
    static inline int keyCount = 0;
    KeyboardKey() : key(keyCount) {keyCount++;}
    explicit KeyboardKey(const GLint key) : key(key) {}
};


struct Window
{
    GLFWwindow* window{};

    static constexpr int WIDTH = 1280;
    static constexpr int HEIGHT = 720;
    static constexpr float halfWidth = static_cast<float>(WIDTH)/2.0f;
    static inline float halfHeight = static_cast<float>(HEIGHT)/2.0f;

    static inline auto mouse = Mouse(true,halfWidth, halfHeight);
    static inline auto camera = Camera({0,0,3}, {0,0,-1});

    float lastFrameTime = 0.0f;
    float currentFrameTime = 0.0f;
    float deltaTime = 0.0f;
    float frameCounter = 0;

    int currentUIElement = 0;
    bool combatUIStart = false;
    bool combatUIMain = false;
    bool combatUISkills = false;
    bool combatUIActionComplete = false;

    static inline std::array<KeyboardKey,GLFW_KEY_LAST+1> keyboardKeys;


    Window();
    ~Window();
    void Init();
    GLFWwindow* operator()() const {return window;}

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void zoom_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    [[nodiscard]] bool isKeyPressed(int key) const;

    void processInput();
    void processMovementInput() const;
    void UpdateDeltaTime();

    static bool positiveEdgeCheck(GLFWwindow* window, GLint key);
    static bool negativeEdgeCheck(GLFWwindow* window, GLint key);
    static int processCombatUIInput(GLFWwindow* window, int currentUIElement, int maxUIElements);
    void FPSCounterTitle();
};