#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

class Texture
{
public:
    Texture(const std::string& filepath);
    ~Texture();

    GLuint GetTexture() { return m_Texture; }

private:
    GLuint m_Texture;
};