#pragma once
#include "Manager.h"
#include "Player.h"
#include "Agent.h"
#include "Enemy.h"
#include "Engine/Vector.h"
#include <vector>
struct MeleeMouse
{
    bool flag;
    Vector<2> location;
};
class EntityManager :public Manager
{
public:
    std::vector<Agent*> agents;
    std::vector<Player*> players;
    std::vector<Enemy*> enemies;
    
    void  Start();
    void Update();
    void    End();
    void entCollision();
    void misCollision();
    MeleeMouse mouseCollision(float x, float y);
    void addAgent(Agent* agent);
    void addPlayer(Player* player);
    void addEnemy(Enemy* enemy);
    void checkState();
};