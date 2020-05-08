#pragma once

#include <SDL2/SDL.h>
#include <tuple>
#include <map>
#include <string>

class InputSystem
{
public:
    InputSystem();
    ~InputSystem();

    bool BindButton(std::string buttonName, int keyCode);
    bool UnbindButton(std::string buttonName);

    bool GetButton(std::string buttonName);
    bool GetButtonDown(std::string buttonName);
    bool GetButtonUp(std::string buttonName);

    void Update();

private:
    typedef std::tuple<std::string, bool, bool> Button;
    std::map<int, Button> m_ButtonMap;
};