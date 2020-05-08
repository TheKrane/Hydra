#pragma once

#include "Component.hpp"

#include "RenderSystem.hpp"

class CameraComponent : public Component
{
public:
    CameraComponent();
    ~CameraComponent();

    void Register();

private:
    //TODO: fov, clipping planes, clear color, skybox, etc.
};