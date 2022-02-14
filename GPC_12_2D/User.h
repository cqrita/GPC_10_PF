#pragma once
#include "Player.h"
#include "EntityManager.h"
static const float doubleTapConst = 0.1f;

class User 
{
public:
    
    void  Start();
    void Update();
    void    End();
    void checkInput();
    void moveInput();
    void attackInput();
    void meleeInput();
    void getPlayer(Player* player);
    void getEntityManager(EntityManager* entityManager);
    float getMouseX();
    float getMouseY();
    
    void moveInputM();
public:
    Engine::Rendering::Camera camera;
private:
    Player* player = nullptr;
    EntityManager* entityManager = nullptr;
    float doubleTap = 0.05f;
    bool doubleTapFlag = false;
};

