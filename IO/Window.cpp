//
// Created by schan on 26/12/2025.
//

#include "Window.hpp"

Window::Window()
{
    Init();
}

Window::~Window()
{
    glfwTerminate();
}

void Window::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //creating window
    window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    //window safety check
    if (window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window.\n");
    }
    glfwMakeContextCurrent(window);

    //glad safety check
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw std::runtime_error("Failed to initialize GLAD.\n");
    }

    std::cout << "AAAAAAAAAAAAA LOL\n";

    glViewport(0,0,WIDTH,HEIGHT);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, zoom_callback);
    glfwSetKeyCallback(window, key_callback);

    lastFrameTime = 0.0f;
}


void Window::framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
}

void Window::mouse_callback(GLFWwindow* window, const double xpos, const double ypos)
{
    if (mouse.locked || !mouse.hidden) {return;}
    if (mouse.firstMove)
    {
        mouse.lastX = static_cast<float>(xpos);
        mouse.lastY = static_cast<float>(ypos);
        mouse.firstMove = false;
    }
    float xoffset = static_cast<float>(xpos) - mouse.lastX;
    float yoffset = mouse.lastY - static_cast<float>(ypos); //screen coords have reversed y axis
    mouse.lastX = static_cast<float>(xpos);
    mouse.lastY = static_cast<float>(ypos);

    camera.UpdateCamera({xoffset, yoffset});
}

void Window::zoom_callback(GLFWwindow* window, const double xoffset, const double yoffset)
{
    camera.ModifyCameraFOV(-static_cast<float>(yoffset));
}

void Window::key_callback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
{
    if (key == GLFW_KEY_0 && action == GLFW_PRESS)
    {
        mouse.hidden = !mouse.hidden;
        if (!mouse.hidden)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }


}

bool Window::isKeyPressed(const int key) const
{
    return (glfwGetKey(window, key) == GLFW_PRESS);
}

void Window::processInput()
{
    if (isKeyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }
    glPolygonMode(GL_FRONT_AND_BACK, isKeyPressed(GLFW_KEY_TAB) ? GL_LINE : GL_FILL);

    if (isKeyPressed(GLFW_KEY_1))
    {
        combatUIStart = true;
        combatUIMain = true;
    }
}

void Window::processMovementInput() const
{
    camera.speed = deltaTime*(isKeyPressed(GLFW_KEY_LEFT_SHIFT) ? 6.0f : 2.25f);

    if (isKeyPressed(GLFW_KEY_W))
    {
        camera.ModifyCameraPos(camera.GetPlaneFacingDirection()*camera.speed);
    }
    if (isKeyPressed(GLFW_KEY_S))
    {
        camera.ModifyCameraPos(-camera.GetPlaneFacingDirection()*camera.speed);
    }
    if (isKeyPressed(GLFW_KEY_A))
    {
        camera.ModifyCameraPos(camera.GetLeftDirection()*camera.speed);
    }
    if (isKeyPressed(GLFW_KEY_D))
    {
        camera.ModifyCameraPos(-camera.GetLeftDirection()*camera.speed);
    }
    if (isKeyPressed(GLFW_KEY_SPACE) && camera.GetPosition().y == 0.0f)
    {
        camera.velocity += camera.GetUpDirection()*camera.speed*100.0f;
    }
    if (isKeyPressed(GLFW_KEY_LEFT_CONTROL))
    {
        camera.ModifyCameraPos(-camera.GetUpDirection()*camera.speed);
    }
}


void Window::UpdateDeltaTime()
{
    currentFrameTime = static_cast<float>(glfwGetTime());
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}






int cyclicIndexUp(const int index, const int max)
{
    return (index + 1 == max) ? 0 : index + 1;
}

int cyclicIndexDown(const int index, const int max)
{
    return (index - 1 == -1) ? max - 1 : index - 1;
}



bool Window::positiveEdgeCheck(GLFWwindow* window, const GLint key)
{
    if (glfwGetKey(window, key) == GLFW_PRESS)
    {
        if (!keyboardKeys[key].wasPressed)
        {
            keyboardKeys[key].wasPressed = true;
            return true;
        }
        return false;
    }
    keyboardKeys[key].wasPressed = false;
    return false;
}

bool Window::negativeEdgeCheck(GLFWwindow* window, const GLint key)
{
    if (glfwGetKey(window, key) == GLFW_RELEASE)
    {
        if (keyboardKeys[key].wasPressed)
        {
            keyboardKeys[key].wasPressed = false;
            return true;
        }
        return false;
    }
    keyboardKeys[key].wasPressed = true;
    return false;
}

int Window::processCombatUIInput(GLFWwindow* window, const int currentUIElement, const int maxUIElements)
{
    if (positiveEdgeCheck(window, GLFW_KEY_LEFT))
    {
        return cyclicIndexDown(currentUIElement, maxUIElements);
    }
    if (positiveEdgeCheck(window, GLFW_KEY_RIGHT))
    {
        return cyclicIndexUp(currentUIElement, maxUIElements);
    }
    return currentUIElement;
}

