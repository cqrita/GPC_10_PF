#pragma once
#include "Entity.h"
#include "Engine/Vector.h"
#include "Engine/Rendering.h"
#include <vector>
#include "Missile.h"
class Pet : public Entity
{
public:
    void  Start() final override;
    void Update() final override;
    void    End() final override;
    void moveUpdate();
    void getCam(Vector<2> location);
    void createMissile(float x, float y);
    void getEnemy(Vector<2> location);
    void getPlayer(Vector<2> location);
public:
    std::vector<Missile*> missiles;
    Engine::Rendering::Animation::Component skin;
    Vector<2> cam;
    int damage = 1;
    Vector<2> enemy;
    Vector<2> player;
private:
    
    float speed;
    float angle;
    float attackSpeed = 0.5f;
    float attackDuration;
    bool attack = false;
};