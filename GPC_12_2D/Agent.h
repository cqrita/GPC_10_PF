#pragma once
#include "Entity.h"
#include "Engine/Quadrangle.h"
#include "Engine/Physics.h"
class Agent abstract : public Entity
{
public:
    virtual void  Start() abstract;
    virtual void Update() abstract;
    virtual void    End() abstract;
    virtual void misCollide() abstract;
    virtual void entCollide() abstract;
public:
    Engine::Physics::Component<Quadrangle> body;
    int state = 1;
};
