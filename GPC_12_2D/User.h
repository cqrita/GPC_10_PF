#pragma once
#include "Player.h"
class User 
{
public:
    Player* player=nullptr;
    void  Start();
    void Update();
    void    End();
    void checkInput();
    void moveInput();
    void attackInput();
private:
    Engine::Rendering::Camera camera;
};