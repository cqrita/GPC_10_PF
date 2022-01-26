#pragma once
#include <vector>
#include "Agent.h"
#include "Direction.h"
#include "Engine/Quadrangle.h"
#include "Engine/Physics.h"
#include "Engine/Rendering.h"
#include "Missile.h"
class Player final : public Agent
{
public:
    void  Start() final override;
    void Update() final override;
    void    End() final override;
    void createMissile();
    void changeMoveState(Dir direction, const char* state);
    void moveUpdate();
public:
    std::vector<Missile*> missiles;
    Engine::Rendering::Animation::Component skin;
private:   
    Engine::Rendering::Image::Component     box;
    enum class MoveState
    {
        idle,
        move,
        run
    } moveState;
    Dir direction;
    float speed;
};