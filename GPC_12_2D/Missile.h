#pragma once
#include "Entity.h"
#include "Direction.h"
#include "Engine/Circle.h"
#include "Engine/Physics.h"
#include "Engine/Rendering.h"

class Missile final : public Entity
{
public:
    void  Start() final override;
    void Update() final override;
    void    End() final override;
    void moveUpdate();
    Missile();
    ~Missile();
    Missile(float angle,Vector<2> location, Dir direction);
public:
    Engine::Physics::Component<Circle>  body;
    float duration = 0;
    int state = 1;
    float distance = 0;
private:
    Engine::Rendering::Image::Component     box;
    Engine::Rendering::Animation::Component skin;
    Dir direction=Dir::I;
    float angle=0;
    float speed = 0;
    
};