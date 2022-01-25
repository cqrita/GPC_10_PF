#pragma once
#include <vector>
#include "Entity.h"
#include "Direction.h"
#include "Engine/Quadrangle.h"
#include "Engine/Physics.h"
#include "Engine/Rendering.h"
#include "Missile.h"
class Player final : public Entity
{
public:
    void  Start() final override;
    void Update() final override;
    void    End() final override;
public:
    std::vector<Missile*> missiles;
    Engine::Physics::Component<Quadrangle>  body;
private:
    
    
    Engine::Rendering::Animation::Component skin;
    Engine::Rendering::Image::Component     box;

    
    Dir direction;
    float speed;
};