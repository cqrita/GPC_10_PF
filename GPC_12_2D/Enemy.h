#pragma once
#include <vector>
#include "Agent.h"
#include "Direction.h"
#include "Engine/Quadrangle.h"
#include "Engine/Physics.h"
#include "Engine/Rendering.h"
#include "Missile.h"
#include "Engine/Sound.h"
static float deathConst=0.5f;
class Enemy : public Agent
{
public:
    void  Start()  override;
    void Update()  override;
    void    End()  override;
    void misCollide(Missile* missile)  override;
    void entCollide(Agent* agent)  override;
    void moveUpdate(Vector<2> location);
    void move();
    void getCam(Vector<2> location);
    void createMissile(float x, float y);
    void setDamage(int i);
    void setMaxHealth(float i);
    ~Enemy() = default;
public:
    std::vector<Missile*> missiles;
    Engine::Rendering::Animation::Component skin;
    Engine::Rendering::Image::Component     box;
    Engine::Rendering::Image::Component progressBar;
    Engine::Rendering::Image::Component bar;
    Engine::Rendering::Image::Component barBorder;
    Engine::Sound::Effect::Component attackSound;
    Engine::Sound::Effect::Component hitSound;
    Engine::Sound::Effect::Component deathSound;
    Vector<2> cam;
    Vector<2> player;
    int damage;

    Engine::Rendering::Text::Component healthText;
    enum class MoveState
    {
        idle,
        walk,
        run
    } moveState;
    
    Dir direction;
    float speed;
    float constSpeed;
    float angle;

    float colDuration = colConst;
    bool colState = false;

    float attackSpeed = 1.0f;
    float attackCool;
    bool attackCoolFlag = false;

    float attackTime = 0.5f;
    float attackDuration;
    bool attack;

    float deathDuration;
    bool deathState;
    bool exp = false;
};