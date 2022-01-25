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
private:
    Engine::Rendering::Camera camera;
};