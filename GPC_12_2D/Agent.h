#pragma once
#include "Entity.h"
class Agent abstract : public Entity
{
public:
    virtual void  Start() abstract;
    virtual void Update() abstract;
    virtual void    End() abstract;
public:
    Engine::Physics::Component<Quadrangle> body;
};
