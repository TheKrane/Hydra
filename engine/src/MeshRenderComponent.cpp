#include "MeshRenderComponent.hpp"

#include "OBJ_Loader.h"

extern RenderSystem* g_pRenderSystem;

MeshRenderComponent::MeshRenderComponent()
{

}

MeshRenderComponent::~MeshRenderComponent()
{

}

void MeshRenderComponent::Register()
{
    g_pRenderSystem->AddComponent(this);
}

bool MeshRenderComponent::LoadMeshFromObj(const std::string& filepath)
{
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> uvs;
    std::vector<GLfloat> normals;
    std::vector<GLushort> indices;

    objl::Loader objLoader;
    if(!objLoader.LoadFile(filepath))
    {
        std::cout << "Could not load model: " << filepath << std::endl;
        return false;
    }

    objl::Mesh loadedMesh = objLoader.LoadedMeshes[0];


    for(unsigned int i = 0; i < loadedMesh.Vertices.size(); i++)
    {
        // load vertices
        vertices.push_back(loadedMesh.Vertices[i].Position.X);
        vertices.push_back(loadedMesh.Vertices[i].Position.Y);
        vertices.push_back(loadedMesh.Vertices[i].Position.Z);
    
        // load uvs
        uvs.push_back(loadedMesh.Vertices[i].TextureCoordinate.X);
        uvs.push_back(loadedMesh.Vertices[i].TextureCoordinate.Y);

        // load normals
        normals.push_back(loadedMesh.Vertices[i].Normal.X);
        normals.push_back(loadedMesh.Vertices[i].Normal.Y);
        normals.push_back(loadedMesh.Vertices[i].Normal.Z);
    }

    for(unsigned int i = 0; i < loadedMesh.Indices.size(); i++)
    {
        // load indices
        indices.push_back(loadedMesh.Indices[i]);
    }

    //Generate buffers
    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_UVBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_UVBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(GLfloat), &uvs[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_NormalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_NormalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), &indices[0], GL_STATIC_DRAW);

    return true;
}