#pragma once

#include "Component.hpp"

#include <string>

class LogicComponent : public Component
{
public:
    LogicComponent();
    ~LogicComponent();

    void Register();

    virtual void Update() = 0;
};