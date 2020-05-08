#include "Entity.hpp"

#include "Component.hpp"

Entity::Entity() : m_Position(glm::vec3(0.0f)), m_Rotation(glm::identity<glm::quat>()), m_Scale(glm::vec3(1.0f))
{

}

Entity::~Entity()
{

}

void Entity::AddComponent(Component* pComponent)
{
    //Add component to components vector
    m_Components.push_back(pComponent);

    //Set entity this components belongs to
    pComponent->SetEntity(this);

    //Register component with correct system
    pComponent->Register();
}