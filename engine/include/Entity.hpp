#pragma once

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Component.hpp"

class Entity
{
public:
    Entity();
    ~Entity();

    void AddComponent(Component* pComponent);

    //Getters and setters
    void SetPosition(glm::vec3 position) { m_Position = position; }
    glm::vec3 GetPosition() { return m_Position; }

    void SetRotation(glm::quat rotation) { m_Rotation = rotation; }
    glm::quat GetRotation() { return m_Rotation; }

    void SetScale(glm::vec3 scale) { m_Scale = scale; }
    glm::vec3 GetScale() { return m_Scale; }

    template <typename ComponentType>
    inline ComponentType* GetComponent()
    {
        for(Component* pComponent : m_Components)
        {
            if (ComponentType* cmp = dynamic_cast<ComponentType*>(pComponent))
            {
                return cmp;
            }
        }
        return nullptr;
    }

private:
    //Components
    std::vector<Component*> m_Components;

    //Parameters
    glm::vec3 m_Position;
    glm::quat m_Rotation;
    glm::vec3 m_Scale;
};