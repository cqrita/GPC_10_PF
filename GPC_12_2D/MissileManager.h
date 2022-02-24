#pragma once
#include "Manager.h"
#include <vector>
#include "Missile.h"
class MissileManager :public Manager
{
    void  Start();
    void Update();
    void    End();
    void addMissile();
    std::vector<Missile*> missiles;
};