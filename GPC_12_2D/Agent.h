#pragma once
#include "Entity.h"
#include "Engine/Quadrangle.h"
#include "Engine/Physics.h"
#include "Missile.h"
class Agent abstract : public Entity
{
public:
    virtual void  Start() abstract;
    virtual void Update() abstract;
    virtual void    End() abstract;
    virtual void misCollide(Missile* missile) abstract;
    virtual void entCollide(Agent* agent) abstract;
public:
    Engine::Physics::Component<Quadrangle> body;
    int health = 100;
    int state = 0;
};
