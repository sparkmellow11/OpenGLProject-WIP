cmake_minimum_required(VERSION 3.31)
project(OpenGLStuff)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(IMGUI_SRC
        imgui/imgui_impl_opengl3.h
        imgui/imgui_impl_opengl3.cpp
        imgui/imgui_impl_opengl3_loader.h
        imgui/imgui_impl_glfw.h
        imgui/imgui_impl_glfw.cpp
        imgui/imconfig.h
        imgui/imgui.h
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_internal.h
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h

)

add_executable(OpenGLStuff main.cpp
        glad.c
        Render/Shader.hpp
        Render/Shader.cpp
        stb_image.h
        IO/Camera.cpp
        IO/Camera.hpp
        Render/Mesh.hpp
        Render/Mesh.cpp
        Render/Model.hpp
        Render/Model.cpp
        ${IMGUI_SRC}
        Utils.hpp
        Utils.cpp
        IO/Mouse.hpp
        IO/Mouse.cpp
        IO/Window.hpp
        IO/Window.cpp
        Render/Rectangle.cpp
        Render/Rectangle.hpp
        ImGuiThing.cpp
        ImGuiThing.hpp
        Render/UISystem.cpp
        Render/UISystem.hpp
        UtilsMain.hpp
        Render2DManager.cpp
        Render2DManager.hpp
)


include_directories("C:/Users/schan/OneDrive/Desktop/Third-party/Include")

target_link_libraries(OpenGLStuff PRIVATE "C:/Users/schan/OneDrive/Desktop/Third-party/Libs/libglfw3.a")
target_link_libraries(OpenGLStuff PRIVATE "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22000.0/um/x64/OpenGL32.lib")


target_link_libraries(OpenGLStuff PRIVATE "C:/Users/schan/OneDrive/Desktop/Third-party/Libs/libassimp.dll.a")

target_compile_definitions(OpenGLStuff PRIVATE PROJECT_ROOT="${CMAKE_SOURCE_DIR}")


