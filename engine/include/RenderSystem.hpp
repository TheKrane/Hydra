#pragma once

#define SDL_MAIN_HANDLED

#include <vector>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>
#include "glm/glm.hpp"

class Shader;
class MeshRenderComponent;
class LightComponent;
class CameraComponent;

class RenderSystem
{
public:
    RenderSystem(const std::string& windowTitle, unsigned int windowWidth, unsigned int windowHeight);
    ~RenderSystem();

    void HandleEvents(bool* pQuit);

    void Render();

    Shader* CreateShader(const std::string &filepath);

    void AddComponent(MeshRenderComponent* pMeshRenderComponent);
    void AddComponent(LightComponent* pLightComponent);

    void SetMainCameraComponent(CameraComponent* pCameraComponent);

    SDL_GLContext* GetGLContext() { return m_pGLContext; }

private:
    //SDL
    SDL_Window* m_pWindow;
    SDL_GLContext* m_pGLContext;

    //Window parameters
    std::string m_WindowTitle;
    unsigned int m_WindowWidth, m_WindowHeight;

    //Shaders
    Shader* m_pCurrentShader;
    std::vector<Shader*> m_Shaders;

    //Components
    std::vector<MeshRenderComponent*> m_MeshRenderComponents;
    std::vector<LightComponent*> m_LightComponents;
    CameraComponent* m_pMainCameraComponent;

    //Temp
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
};
