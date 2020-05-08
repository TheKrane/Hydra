#include "RenderSystem.hpp"

#include <iostream>
#include <stdexcept>

#include "Entity.hpp"
#include "Shader.hpp"
#include "MeshRenderComponent.hpp"
#include "LightComponent.hpp"
#include "CameraComponent.hpp"

#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"

#include <chrono>

RenderSystem::RenderSystem(const std::string& windowTitle, unsigned int windowWidth, unsigned int windowHeight)
{
    //Set window properties
    m_WindowTitle = windowTitle;
    m_WindowWidth = windowWidth;
    m_WindowHeight = windowHeight;

    //Create SDL window
    m_pWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(!m_pWindow)
        throw std::runtime_error("Window could not be created: " + std::string(SDL_GetError()));

    //Set OpenGl parameters
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    //Create OpenGL context
    SDL_GLContext m_pGLContext = SDL_GL_CreateContext(m_pWindow);
    if(!m_pGLContext)
        throw std::runtime_error("OpenGL conext could not be created: " + std::string(SDL_GetError()));

    glewExperimental = true;
    glewInit();

    //Create Vertex Array Object
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glEnable(GL_DEPTH_TEST);  

    glEnable(GL_CULL_FACE);  
    glCullFace(GL_BACK); 

    //Set clear color
    glClearColor(0.4f, 0.8f, 1.0f, 0.0f);
    
    //Set OpenGL viewport
    glViewport(0, 0, m_WindowWidth, m_WindowHeight);
}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::HandleEvents(bool* pQuit)
{
    //Poll all events
    SDL_Event event;

    while(SDL_PollEvent(&event) != 0)
    {
        //Check if event is quit
        if(event.type == SDL_QUIT)
            *pQuit = true;
    }
}

void RenderSystem::Render()
{
    //Clear the screen
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //Render mesh components
    for(Shader* pShader : m_Shaders)
    {
        m_pCurrentShader = pShader;
        pShader->Use();

        //Bind camera matrice
        glm::vec3 cameraPosition = m_pMainCameraComponent->GetEntity()->GetPosition();

        m_ProjectionMatrix = glm::perspective(glm::radians(90.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 1000.0f);
        m_ViewMatrix = glm::lookAt(cameraPosition, cameraPosition + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint projectionUniform = glGetUniformLocation(pShader->GetShaderProgram(), "ProjectionMatrix");
        if (projectionUniform == -1) 
            std::cout << "Could not bind projection matrix uniform!" << std::endl;
        glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, &m_ProjectionMatrix[0][0]);
        
        GLint ViewUniform = glGetUniformLocation(pShader->GetShaderProgram(), "ViewMatrix");
        if (ViewUniform == -1) 
            std::cout << "Could not bind view matrix uniform" << std::endl;
        glUniformMatrix4fv(ViewUniform, 1, GL_FALSE, &m_ViewMatrix[0][0]);

        GLint PositionUniform = glGetUniformLocation(pShader->GetShaderProgram(), "CameraPosition");
        if (ViewUniform == -1) 
            std::cout << "Could not bind camera position uniform" << std::endl;
        glUniform3f(PositionUniform, cameraPosition.x, cameraPosition.y, cameraPosition.z);

        //Bind lights
        for(LightComponent* pLight : m_LightComponents)
        {
            //Get entity values
            glm::vec3 position = pLight->GetEntity()->GetPosition();
            glm::vec3 eulerAngles = glm::eulerAngles(pLight->GetEntity()->GetRotation()) * 3.1415926f / 180.f;

            //Bind Type
            GLint typeUniform = glGetUniformLocation(m_pCurrentShader->GetShaderProgram(), ("Lights[" + std::to_string(pLight->GetIndex()) + "].Type").c_str());
            if(typeUniform == -1)
                std::cout << "Could not bind light type uniform!" << std::endl;
            glUniform1i(typeUniform, pLight->GetLightType());

            //Bind Position
            GLint positionUniform = glGetUniformLocation(m_pCurrentShader->GetShaderProgram(), ("Lights[" + std::to_string(pLight->GetIndex()) + "].Position").c_str());
            if(positionUniform == -1)
                std::cout << "Could not bind light position uniform!" << std::endl;
            glUniform3f(positionUniform, position[0], position[1], position[2]);

            //Bind Rotation
            GLint rotationUniform = glGetUniformLocation(m_pCurrentShader->GetShaderProgram(), ("Lights[" + std::to_string(pLight->GetIndex()) + "].Rotation").c_str());
            if(rotationUniform == -1)
                std::cout << "Could not bind light rotation uniform!" << std::endl;
            glUniform3f(rotationUniform, eulerAngles[0], eulerAngles[1], eulerAngles[2]);

            //Bind Intensity
            GLint intensityUniform = glGetUniformLocation(m_pCurrentShader->GetShaderProgram(), ("Lights[" + std::to_string(pLight->GetIndex()) + "].Intensity").c_str());
            if(intensityUniform == -1)
                std::cout << "Could not bind light intensity uniform!" << std::endl;
            glUniform3f(intensityUniform, pLight->GetIntensity()[0], pLight->GetIntensity()[1], pLight->GetIntensity()[2]);

            //Bind Diffuse
            GLint ambientUniform = glGetUniformLocation(m_pCurrentShader->GetShaderProgram(), ("Lights[" + std::to_string(pLight->GetIndex()) + "].Ambient").c_str());
            if(ambientUniform == -1)
                std::cout << "Could not bind light ambient uniform!" << std::endl;
            glUniform1f(ambientUniform, pLight->GetAmbient());
        }

        //Draw
        for(MeshRenderComponent* pMesh : m_MeshRenderComponents)
        {
            //Draw only if shader is current shader (TODO: optimize this)
            if(m_pCurrentShader == pMesh->GetMaterial()->GetShader())
            {
                //Bind buffers
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, pMesh->m_VertexBuffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 

                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, pMesh->m_UVBuffer);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); 

                glEnableVertexAttribArray(2);
                glBindBuffer(GL_ARRAY_BUFFER, pMesh->m_NormalBuffer);
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pMesh->m_IndexBuffer);
                GLint size; 
                glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

                //Create model matrix
                glm::mat4 modelMatrix = glm::mat4(1.0f) *
                                        glm::translate(pMesh->GetEntity()->GetPosition()) *
                                        glm::mat4_cast(pMesh->GetEntity()->GetRotation()) *
                                        glm::scale(pMesh->GetEntity()->GetScale());

                //Bind model matrix to shader
                GLint modelMatrixUniform = glGetUniformLocation(m_pCurrentShader->GetShaderProgram(), "ModelMatrix");
                if (modelMatrixUniform == -1) 
                    std::cout << "Could not bind model matrix uniform!" << std::endl;
                glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, &(modelMatrix[0][0]));

                //Bind other attributes
                pMesh->GetMaterial()->BindAttributes();

                //Draw
                glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

                //Disable vertex attributes
                glDisableVertexAttribArray(0);
            }
        }
    }

    //Swap buffers
    SDL_GL_SwapWindow(m_pWindow);
}

Shader* RenderSystem::CreateShader(const std::string& filepath)
{
    try
    {
        Shader* pShader = new Shader(filepath);
        m_Shaders.push_back(pShader);

        return pShader;
	}
    catch(const std::exception& e)
    {
		std::cout << e.what() << std::endl;
        return nullptr;
	}
}

void RenderSystem::AddComponent(MeshRenderComponent* pMeshRenderComponent)
{
    m_MeshRenderComponents.push_back(pMeshRenderComponent);
}

void RenderSystem::AddComponent(LightComponent* pLightComponent)
{
    m_LightComponents.push_back(pLightComponent);
}

void RenderSystem::SetMainCameraComponent(CameraComponent* pCameraComponent)
{
    m_pMainCameraComponent = pCameraComponent;
}