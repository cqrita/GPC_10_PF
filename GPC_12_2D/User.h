#pragma once
#include "Player.h"
class User 
{
public:
    
    void  Start();
    void Update();
    void    End();
    void checkInput();
    void moveInput();
    void attackInput();
    void getPlayer(Player* player);
    float getMouseX();
    float getMouseY();
public:
    Engine::Rendering::Camera camera;
private:
    Player* player = nullptr;
    
};

