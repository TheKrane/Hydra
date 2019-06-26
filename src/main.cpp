#include <Hydra/RenderSystem/OpenGLRenderSystem.hpp>

RenderSystem* g_pRenderSystem = nullptr;

int main()
{
    //Initialize systems
    g_pRenderSystem = new OpenGLRenderSystem();
    g_pRenderSystem->Initialize("Demo", 1080, 720);

    //Main loop
    while(!g_pRenderSystem->m_Quit)
    {
        g_pRenderSystem->Update();
        g_pRenderSystem->Render();
    }
    
    //Shutdown
    delete g_pRenderSystem;
    g_pRenderSystem = nullptr;

    return 0;
}