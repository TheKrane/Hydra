#pragma once

#include <string>

class RenderSystem
{
public:
    RenderSystem();
    ~RenderSystem();

    virtual bool Initialize(const std::string& windowTitle, unsigned int windowWidth, unsigned int windowHeight) = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;

    bool m_Quit;
};