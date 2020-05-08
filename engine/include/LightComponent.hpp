#pragma once

#include "Component.hpp"

#include "RenderSystem.hpp"

enum LightType
{
    PointLight,
    DirectionalLight
};

class LightComponent : public Component
{
public:
    LightComponent(LightType lightType, int index);
    ~LightComponent();

    void Register();

    void BindToShader(GLuint shaderProgram, int index);

    void SetIntensity(float r, float g, float b) { m_Intensity = glm::vec3(r,g,b); }
    glm::vec3 GetIntensity() { return m_Intensity; };

    void SetAmbient(float value) { m_Ambient = value; }
    float GetAmbient() { return m_Ambient; }

    LightType GetLightType() { return m_LightType; };
    int GetIndex() { return m_Index; }

private:
    LightType m_LightType;
    glm::vec3 m_Intensity;
    float m_Ambient;

    int m_Index;
};