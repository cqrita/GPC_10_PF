#pragma once

class Entity abstract
{
public:
    virtual void  Start() abstract;
    virtual void Update() abstract;
    virtual void    End() abstract;
};