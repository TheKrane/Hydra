#pragma once

#include <vector>

class ColliderComponent;

class PhysicsSystem
{
public:
    PhysicsSystem();
    ~PhysicsSystem();

    void Update();

    void AddComponent(ColliderComponent* pColliderComponent);

private:
    std::vector<ColliderComponent*> m_ColliderComponents;
};