#include <Hydra/RenderSystem/OpenGLRenderSystem.hpp>

#include <iostream>

OpenGLRenderSystem::OpenGLRenderSystem() : m_pWindow(nullptr)
{

}

OpenGLRenderSystem::~OpenGLRenderSystem()
{
    //Terminate ImGUI
    //ImGui_ImplGlfwGL3_Shutdown();
    //ImGui::DestroyContext();

    //Terminate glfw
    glfwTerminate();
}

bool OpenGLRenderSystem::Initialize(const std::string& windowTitle, unsigned int windowWidth, unsigned int windowHeight)
{
    //Set window properties
    m_WindowTitle = windowTitle;
    m_WindowWidth = windowWidth;
    m_WindowHeight = windowHeight;

    // initialize GLFW
    if( !glfwInit() )
    {
        std::cout <<  "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); //4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    m_pWindow = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_WindowTitle.c_str(), nullptr, nullptr);
    if(m_pWindow == nullptr )
    {
        std::cout << "GFLW window could not be created!" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_pWindow);

    // initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum res = glewInit();
    if (res != GLEW_OK) 
    {
        std::cout << "Could not initialize GLEW: " << glewGetErrorString(res) << std::endl;
        return false;
    }

    // create Vertex Array Object
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // set clear color
    glClearColor(0.4, 0.8, 1.0, 0.0);
    // enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    // enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // set OpenGL viewport
    int w, h;
    glfwGetFramebufferSize(m_pWindow, &w, &h);
    glViewport(0, 0, w, h);

    // Setup ImGui binding
    /*IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfwGL3_Init(m_pWindow, true);*/

    return true;
}

void OpenGLRenderSystem::Update()
{
    //Poll events
    glfwPollEvents();

    //Close window
    if(glfwWindowShouldClose(m_pWindow))
        m_Quit = true;

    //Start new ImGui frame
    //ImGui_ImplGlfwGL3_NewFrame();
}

void OpenGLRenderSystem::Render()
{
    
}