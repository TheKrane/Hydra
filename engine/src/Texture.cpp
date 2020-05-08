#include "Texture.hpp"

#include <iostream>

Texture::Texture(const std::string& filepath)
{
    SDL_Surface* pSurface = IMG_Load(filepath.c_str());
 
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    
    int mode = GL_RGB;
    
    if(pSurface->format->BytesPerPixel == 4) {
        mode = GL_RGBA;
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, mode, pSurface->w, pSurface->h, 0, mode, GL_UNSIGNED_BYTE, pSurface->pixels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{

}

