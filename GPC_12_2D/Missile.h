#pragma once
#include "Entity.h"
#include "Direction.h"
#include "Engine/Circle.h"
#include "Engine/Physics.h"
#include "Engine/Rendering.h"

class Missile  : public Entity
{
public:
    void  Start()  override;
    void Update()  override;
    void    End()  override;
    void moveUpdate();
    void getEnemy(Vector<2> location);
    float changeAngle();
    void getDamage(int damage);
    Missile();
    ~Missile();
    Missile(float angle,Vector<2> location , Vector<2> user);
public:
    Engine::Physics::Component<Circle>  body;
    float duration = 0;
    int state = 1;
    float distance = 0;
    Vector<2> enemy;
    bool EnemyHoming = false;
    int damage = 10;

    Engine::Rendering::Image::Component     box;
    Engine::Rendering::Animation::Component skin;
    float angle=0;
    float speed = 0;
    
};