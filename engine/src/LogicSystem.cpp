#include "LogicSystem.hpp"

#include <iostream>

LogicSystem::LogicSystem()
{
    
}

LogicSystem::~LogicSystem()
{

}

void LogicSystem::Update()
{
    for(LogicComponent* pLogicComponent : m_LogicComponents)
        pLogicComponent->Update();
}

void LogicSystem::AddComponent(LogicComponent* pLogicComponent)
{
    m_LogicComponents.push_back(pLogicComponent);
}