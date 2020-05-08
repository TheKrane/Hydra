#include "LogicComponent.hpp"

#include "LogicSystem.hpp"

extern LogicSystem* g_pLogicSystem;

LogicComponent::LogicComponent()
{
}

LogicComponent::~LogicComponent()
{
    
}

void LogicComponent::Register()
{
    g_pLogicSystem->AddComponent(this);
}