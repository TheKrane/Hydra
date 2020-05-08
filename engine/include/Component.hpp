#pragma once

class Entity;

class Component
{
public:
    Component() {};
    ~Component() {};

    //Getters and setters
    void SetEntity(Entity* pEntity) { m_pEntity = pEntity; }
    Entity* GetEntity() { return m_pEntity; }

    //Virtual members
    virtual void Register() = 0;

private:
    Entity* m_pEntity;
};