#pragma once
#include "Entity.h"
#include "Engine/Rendering.h"
#include "Engine/Physics.h"
#include "Engine/Quadrangle.h"
class Item : public Entity
{
public:
    void  Start()  override;
    void Update()  override;
    void    End()  override;
    void getCam(Vector<2> location);
    void onCollide();
public:
    Engine::Rendering::Animation::Component skin;
    Engine::Physics::Component<Quadrangle> body;
    Vector<2> cam;
    int state = 0;
    enum class ItemValue
    {
        Health,
        MissilePower,
        Count
    }itemValue;
    int itemNum = 0;
private:
    const float colConst = 1.0f;
    float colDuration = colConst;
    bool colState = false;
};