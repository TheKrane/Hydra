#pragma once

#include "Component.hpp"

#include "RenderSystem.hpp"
#include "Material.hpp"

class MeshRenderComponent : public Component
{
public:
    MeshRenderComponent();
    ~MeshRenderComponent();

    GLuint m_VertexBuffer;
    GLuint m_UVBuffer;
    GLuint m_NormalBuffer;
    GLuint m_IndexBuffer;

    void Register();

    bool LoadMeshFromObj(const std::string& filepath);

    void SetMaterial(Material* pMaterial) { m_pMaterial = pMaterial; }
    Material* GetMaterial() { return m_pMaterial; }

private:
    Material* m_pMaterial;
};