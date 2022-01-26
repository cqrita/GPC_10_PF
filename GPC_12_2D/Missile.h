#pragma once
#include "Entity.h"
#include "Direction.h"
#include "Engine/Quadrangle.h"
#include "Engine/Physics.h"
#include "Engine/Rendering.h"

class Missile final : public Entity
{
public:
    void  Start() final override;
    void Update() final override;
    void    End() final override;
    ~Missile()=default;
public:
    Engine::Physics::Component<Quadrangle>  body;
private:
    Engine::Rendering::Image::Component     box;
    Engine::Rendering::Animation::Component skin;
    
    float angle;
    float speed;
    float duration;
};