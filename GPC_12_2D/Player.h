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
    void misCollide() final override;
    void entCollide() final override;
    void createMissile();
    void changeMoveState(Dir direction, const char* state);
    void moveUpdate();

public:
    std::vector<Missile*> missiles;
    Engine::Rendering::Animation::Component skin;
    Engine::Rendering::Image::Component     box;

private:   
    
    enum class MoveState
    {
        idle,
        walk,
        run
    } moveState;

    Dir direction;
    Dir preDirection;
    float speed;
    float attackspeed;
    bool attack = false;
};