#pragma once

#include "LogicComponent.hpp"

#include <utility>

template<typename Callback>
class CallbackLogicComponent : public LogicComponent
{
    Callback callback;

public:
    CallbackLogicComponent(Callback&& callback) : callback(std::forward<Callback>(callback))
    {

    }

    void Update() override
    {
        callback(GetEntity());
    }
};

template<typename Callback>
CallbackLogicComponent(Callback&& callback) -> CallbackLogicComponent<Callback>;