//
// Created by schan on 24/08/2025.
//

#include "Shader.hpp"

#include "../Utils.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file’s buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    };
    // similiar for Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    };

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
        infoLog << std::endl;
    }
    // delete shaders; they’re linked into our program and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void Shader::use() const
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, const bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, const int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, const float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, const float *matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, matrix);
}

void Shader::setVec4(const std::string& name, const float *vec) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, vec);
}





void Shader::setModelMatrix(const glm::vec3& translation, const glm::vec3& scaling,
                            const float rotation, const glm::vec3& rotationAxis)
{
    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, translation);
    modelMatrix = glm::scale(modelMatrix, scaling);
    modelMatrix = glm::rotate(modelMatrix, rotation, rotationAxis);
    setMat4("model", glm::value_ptr(modelMatrix));

}

void Shader::setModelMatrix(const glm::vec3& translation, const glm::vec3& scaling)
{
    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, translation);
    modelMatrix = glm::scale(modelMatrix, scaling);
    setMat4("model", glm::value_ptr(modelMatrix));
}

void Shader::setModelMatrix(const glm::vec3& translation, const glm::vec3& scaling,
    const float colatitude, const float azimuth)
{
    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, translation);
    modelMatrix = glm::scale(modelMatrix, scaling);
    modelMatrix = glm::rotate(modelMatrix, colatitude, -unitZ);
    modelMatrix = glm::rotate(modelMatrix, azimuth, unitY);
    setMat4("model", glm::value_ptr(modelMatrix));
}

void Shader::setOrthoProjMatrix(const float halfWidth, const float halfHeight)
{
    auto projectionMatrix = glm::ortho(-halfWidth,halfWidth,-halfHeight,halfHeight,-1.0f,1.0f);
    setMat4("projection", glm::value_ptr(projectionMatrix));
}

void Shader::setPerspProjMatrix(const float fov, const float width, const float height)
{
    auto projectionMatrix = glm::perspective(glm::radians(fov), width/height, 0.1f, 100.0f);
    setMat4("projection", glm::value_ptr(projectionMatrix));
}

void Shader::setViewMatrix(const glm::mat4& viewMatrix) const
{
    setMat4("view", glm::value_ptr(viewMatrix));
}
