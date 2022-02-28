#pragma once
#include <vector>
#include "Agent.h"
#include "Direction.h"
#include "Engine/Quadrangle.h"
#include "Engine/Physics.h"
#include "Engine/Rendering.h"
#include "Engine/Sound.h"
#include "Missile.h"
#include "Pet.h"
#include "Item.h"
static const int playerWidth = 25;
static const int playerHeight = 33;
static const float attackConst = 10.0f;
static const float runConst = 0.2f;
static const float itemConst = 0.5f;


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

    void getItem(Item* item);

    void getExp(int value);
    void lvlUp();

public:
    std::vector<Pet*> pets;
    std::vector<Missile*> missiles;
    Engine::Rendering::Animation::Component skin;
    Engine::Rendering::Animation::Component muzzle;
    Engine::Rendering::Animation::Component item;
    Engine::Rendering::Image::Component     box;
    Engine::Rendering::Text::Component levelImage;
    Engine::Sound::Effect::Component shoot;
    Engine::Sound::Effect::Component walk;
    Engine::Sound::Effect::Component pickUp;
    float attackSpeed = 100.0f;
    float runCooltime = 1.0f;
    float walkSpeed = 400;
    float runSpeed = 1000; 
    int damage = 10;
    Vector<2> cam;

    int petNum;

    float level;
    float exp;


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
    Engine::Rendering::Image::Component progressBar;
    Engine::Rendering::Image::Component bar;
    Engine::Rendering::Image::Component barBorder;

    Engine::Rendering::Image::Component lvlprogressBar;
    Engine::Rendering::Image::Component lvlbar;
    Engine::Rendering::Image::Component lvlbarBorder;


    float speed;
    float attackDuration;
    float runDuration;
    float runCoolDuration;
    bool attackTime = false;
    bool attack = false;
    bool run = false;
    bool runCool = false;

    float angle;
    float preAngle;

    float colDuration = colConst;
    bool colState = false;

    float itemDuration = itemConst;
    bool itemState = false;
    
    bool walkState;
};