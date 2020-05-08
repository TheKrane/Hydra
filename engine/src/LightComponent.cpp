#include "LightComponent.hpp"

extern RenderSystem* g_pRenderSystem;

LightComponent::LightComponent(LightType lightType, int index)
{
    m_LightType = lightType;
    m_Intensity = glm::vec3(1.0f, 1.0f, 1.0f);
    m_Ambient = 1.0f;

    m_Index = index;
}

LightComponent::~LightComponent()
{

}

void LightComponent::Register()
{
    g_pRenderSystem->AddComponent(this);
}