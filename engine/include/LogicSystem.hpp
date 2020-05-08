#pragma once

#include <vector>
#include <string>

#include "LogicComponent.hpp"

class LogicSystem
{
public:
    LogicSystem();
    ~LogicSystem();

    void Update();

    void AddComponent(LogicComponent* pLogicComponent);

private:
    //Components
    std::vector<LogicComponent*> m_LogicComponents;
};