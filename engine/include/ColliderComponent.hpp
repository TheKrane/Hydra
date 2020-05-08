#pragma once

#include "Component.hpp"

#include <vector>
#include <glm/glm.hpp>

class ColliderComponent : public Component
{
public:
    void Register() override;
};