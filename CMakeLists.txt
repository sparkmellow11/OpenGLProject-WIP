cmake_minimum_required(VERSION 3.31)
project(OpenGLStuff)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)

#-------------------------------------------------------------
# OPENGL
find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# ASSIMP
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF) # Disable building extra tools
set(ASSIMP_BUILD_TESTS OFF) # Disable building tests
set(ASSIMP_NO_EXPORT ON) #Disable all exporters
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF) # Disable all importers by default
set(ASSIMP_BUILD_OBJ_IMPORTER ON)
set(ASSIMP_BUILD_FBX_IMPORTER ON)

FetchContent_Declare(
  assimp
  GIT_REPOSITORY https://github.com/assimp/assimp.git
  GIT_TAG v5.3.1
)
FetchContent_MakeAvailable(assimp)

# GLAD
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

#---------------------------------------------------------------

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

#---------------------------------------------------------

target_link_libraries(OpenGLStuff
    OpenGL::GL
    glm
    glfw
    assimp
    glad
)


target_compile_definitions(OpenGLStuff PRIVATE PROJECT_ROOT="${CMAKE_SOURCE_DIR}")
