#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

Shader::Shader(const std::string &filepath)
{
    m_ShaderProgram = glCreateProgram();

    // load vertex shader
    if (!LoadShader(filepath + ".vs", GL_VERTEX_SHADER))
        throw std::runtime_error("Could not load shader: " + filepath + ".vs");

    // load fragment shader
    if (!LoadShader(filepath + ".fs", GL_FRAGMENT_SHADER))
        throw std::runtime_error("Could not load shader: " + filepath + ".fs");

    // link shader program
    GLint success;

    glLinkProgram(m_ShaderProgram);
    glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);

    if(success == 0)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_ShaderProgram, maxLength, &maxLength, &infoLog[0]);
        std::string errorString(infoLog.begin(), infoLog.end());

        throw std::runtime_error("Could not link shader program: " + errorString);
    }

    // validate shader program
    glValidateProgram(m_ShaderProgram);
    glGetProgramiv(m_ShaderProgram, GL_VALIDATE_STATUS, &success);

    if(success == 0)
        throw std::runtime_error("Invalid shader program: " + filepath);
}

Shader::~Shader()
{
}


void Shader::Use()
{
    glUseProgram(m_ShaderProgram);
}

bool Shader::BindTexture(const std::string& uniformName, Texture texture)
{
    GLint uniform = glGetUniformLocation(m_ShaderProgram, uniformName.c_str());
    if(uniform == -1)
    {
        std::cout << "Could not bind " << uniformName << " uniform!" << std::endl;
        return false;
    }
    GLuint textureAttribute = texture.GetTexture();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureAttribute);
    glUniform1f(uniform, 0);

    return true;
}

bool Shader::BindFloat(const std::string& uniformName, float value)
{
    GLint uniform = glGetUniformLocation(m_ShaderProgram, uniformName.c_str());
    if(uniform == -1)
    {
        std::cout << "Could not bind " << uniformName << " uniform!" << std::endl;
        return false;
    }
    glUniform1f(uniform, value);

    return true;
}

bool Shader::LoadShader(const std::string &filepath, GLenum shaderType)
{
    // open file
    std::string content;
    std::ifstream fileStream(filepath.c_str());

    if (!fileStream.is_open())
    {
        std::cerr << "Could not read shader file " << filepath << "!" << std::endl;
        return false;
    }

    // read file
    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    // close file
    fileStream.close();

    // compile shader
    GLuint ShaderObject = glCreateShader(shaderType);

    if (ShaderObject == 0)
    {
        std::cout << "Could not create shader object!" << std::endl;
        return false;
    }

    // add shader source to shader
    const char *shaderSource = content.c_str();
    glShaderSource(ShaderObject, 1, &shaderSource, nullptr);

    // compile shader
    GLint success = 0;

    glCompileShader(ShaderObject);
    glGetShaderiv(ShaderObject, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLint maxLength = 0;
        glGetShaderiv(ShaderObject, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(ShaderObject, maxLength, &maxLength, &errorLog[0]);
        std::string errorString(errorLog.begin(), errorLog.end());

        std::cout << "Could not compile shader: " << filepath << "\n" << errorString << std::endl;
        return false;
    }

    // Associate shader with shader program
    glAttachShader(m_ShaderProgram, ShaderObject);

    return true;
}
