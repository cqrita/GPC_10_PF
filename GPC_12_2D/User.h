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
private:
    Player* player = nullptr;
    Engine::Rendering::Camera camera;
};