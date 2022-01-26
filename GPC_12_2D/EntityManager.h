#pragma once
#include "Manager.h"
#include "Player.h"
#include "Agent.h"
#include <vector>
class EntityManager :public Manager
{
public:
    std::vector<Agent*> agents;
    std::vector<Player*> players;
    
    void  Start();
    void Update();
    void    End();
    void entCollision();
};