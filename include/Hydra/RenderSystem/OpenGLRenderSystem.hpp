#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include "RenderSystem.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

class OpenGLRenderSystem : public RenderSystem
{
public:
    OpenGLRenderSystem();
    ~OpenGLRenderSystem();

    bool Initialize(const std::string& windowTitle, unsigned int windowWidth, unsigned int windowHeight);
    void Update();
    void Render();

private:
    //Window properties
    GLFWwindow* m_pWindow;
    std::string m_WindowTitle;
    unsigned int m_WindowWidth, m_WindowHeight;
};