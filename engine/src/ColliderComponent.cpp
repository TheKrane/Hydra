#include "ColliderComponent.hpp"

#include "Entity.hpp"
#include "PhysicsSystem.hpp"

extern PhysicsSystem* g_pPhysicsSystem;

void ColliderComponent::Register()
{
    g_pPhysicsSystem->AddComponent(this);
}