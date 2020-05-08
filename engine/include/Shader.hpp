#pragma once

#include <string>
#include <RenderSystem.hpp>

#include "Texture.hpp"

class Shader
{
public:
    Shader(const std::string &filepath);
    ~Shader();

    void Use();

    bool BindTexture(const std::string& uniformName, Texture texture);
    bool BindFloat(const std::string& uniformName, float value);

    GLuint GetShaderProgram() { return m_ShaderProgram; }

private:
    bool LoadShader(const std::string &filePath, GLenum shaderType);

    GLuint m_ShaderProgram;
};