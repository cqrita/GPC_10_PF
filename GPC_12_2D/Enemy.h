#pragma once
#include <vector>
#include "Agent.h"
#include "Direction.h"
#include "Engine/Quadrangle.h"
#include "Engine/Physics.h"
#include "Engine/Rendering.h"
#include "Missile.h"


class Enemy final : public Agent
{
public:
    void  Start() final override;
    void Update() final override;
    void    End() final override;
    void misCollide(Missile* missile) final override;
    void entCollide(Agent* agent) final override;
    void moveUpdate(Vector<2> location);
    void getCam(Vector<2> location);
    void createMissile(float x, float y);


    ~Enemy() = default;
public:
    std::vector<Missile*> missiles;
    Engine::Rendering::Animation::Component skin;
    Engine::Rendering::Image::Component     box;
    Engine::Rendering::Image::Component healthImage;
    Vector<2> cam;
    int damage = 1;
    int health;
private:
    Engine::Rendering::Text::Component healthText;
    enum class MoveState
    {
        idle,
        walk,
        run
    } moveState;
    
    Dir direction;
    float speed;
    
    float colDuration = colConst;
    bool colState = false;

    float attackSpeed = 0.5f;
    float attackDuration;
    bool attack = false;

};