#include "InputSystem.hpp"

#include <iostream>

InputSystem::InputSystem()
{

}

InputSystem::~InputSystem()
{
}


bool InputSystem::BindButton(std::string buttonName, int keyCode)
{
    Button button(buttonName, false, false);
    m_ButtonMap[keyCode] = button;

    return true;  
}

bool InputSystem::UnbindButton(std::string buttonName)
{
    for (auto it = m_ButtonMap.begin(); it != m_ButtonMap.end(); it++)
    {
        if (std::get<0>(it->second) == buttonName)
        {
            m_ButtonMap.erase(it);
            return true;
        }
    }
    
    return false;
}

bool InputSystem::GetButton(std::string buttonName)
{
    for (auto it = m_ButtonMap.begin(); it != m_ButtonMap.end(); it++)
    {
        if (std::get<0>(it->second) == buttonName && std::get<1>(it->second) == true)
            return true;
    }
    
    return false;
}

bool InputSystem::GetButtonDown(std::string buttonName)
{
    for (auto it = m_ButtonMap.begin(); it != m_ButtonMap.end(); it++)
    {
        if (std::get<0>(it->second) == buttonName && std::get<1>(it->second) == true && std::get<2>(it->second) == false)
            return true;
    }

    return false;
}

bool InputSystem::GetButtonUp(std::string buttonName)
{
    for (auto it = m_ButtonMap.begin(); it != m_ButtonMap.end(); it++)
    {
        if (std::get<0>(it->second) == buttonName && std::get<1>(it->second) == false && std::get<2>(it->second) == true)
            return true;
    }

    return false;
}

void InputSystem::Update()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    //Buttons
    for (auto it = m_ButtonMap.begin(); it != m_ButtonMap.end(); it++)
    {
        Button button = it->second;

        std::get<2>(button) = std::get<1>(button);

        if(state[it->first])
            std::get<1>(button) = true;
        else
            std::get<1>(button) = false;

        it->second = button;
    }
}