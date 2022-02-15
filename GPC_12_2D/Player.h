#pragma once
#include <vector>
#include "Agent.h"
#include "Direction.h"
#include "Engine/Quadrangle.h"
#include "Engine/Physics.h"
#include "Engine/Rendering.h"
#include "Missile.h"
#include "Pet.h"
static const int playerWidth = 25;
static const int playerHeight = 33;
static const float attackConst = 10.0f;
static const float runConst = 0.2f;



class Player final : public Agent
{
public:
    void  Start() final override;
    void Update() final override;
    void    End() final override;
    void misCollide(Missile* missile) final override;
    void entCollide(Agent* agent) final override;
    void createMissile(float x, float y);
    void createMelee(float x, float y);
    void changeMoveState(Dir direction, const char* state);
    void moveUpdate();
    int bkCollide(Vector<2> location);
    void getCam(Vector<2> location);

    void changeMoveStateM(float angle, const char* state);
    void moveUpdateM();
    void createPet();


public:
    std::vector<Pet*> pets;
    std::vector<Missile*> missiles;
    Engine::Rendering::Animation::Component skin;
    Engine::Rendering::Image::Component     box;
    float attackSpeed = 100.0f;
    float runCooltime = 1.0f;
    float walkSpeed = 400;
    float runSpeed = 2000; 
    Vector<2> cam;

    int health;
    int petNum;

private:   
    
    enum class MoveState
    {
        idle,
        walk,
        run
    } moveState;

    Dir direction;
    Dir preDirection;
    Engine::Rendering::Text::Component healthText;
    float speed;
    float attackDuration;
    float runDuration;
    float runCoolDuration;
    bool attack = false;
    bool run = false;
    bool runCool = false;

    float angle;
    float preAngle;

    float colDuration = colConst;
    bool colState = false;
};