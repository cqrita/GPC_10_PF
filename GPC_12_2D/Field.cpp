#include <Windows.h>
#include <iostream>
#include "Field.h"
#include "Global.h"
#include <cstdlib>
#include "Engine/Input.h"
#include "Player.h"
#include "Enemy.h"

void Field::Start()
{
    {
        background.Name = "Image/Celadon";

        background.Length = Vector<2>(bkWidth, bkHeight)*2;
    }
    
    std::srand(static_cast<unsigned int>(time(nullptr)));
    {
        entityManager = new EntityManager;
        user = new User;
        player = new Player;        
        user->Start();
        entityManager->Start();
        player->Start();
        user->getPlayer(player);
        entityManager->addPlayer(player);
    }
}

Scene* Field::Update()
{
    using namespace Engine;
    
    
    

    background.Render();
    entityManager->Update();
    user->Update();
    for (auto e= enemies.begin(); e!=enemies.end() && !enemies.empty();)
    {
        if ((*e)->state==1)
        {
            (*e)->moveUpdate(player->skin.Location);
            (*e)->Update();
            ++e;
        }
        else
        {
            (*e)->End();
            e=enemies.erase(e);
        }
    }
    if (enemies.size()<100)
    {
        int x = rand() % (bkWidth*2)- bkWidth;
        int y = rand() % (bkHeight*2)-bkHeight;
        if ((x < user->camera.Location[0] - camWidth || x > user->camera.Location[0] + camWidth) && (y<user->camera.Location[1] - camHeight || y > user->camera.Location[1] + camHeight))
        {
            Vector<2> enemyLoc = Vector<2>(x, y);

            Enemy* enemy = new Enemy();

            enemies.push_back(enemy);
            entityManager->addAgent(enemy);
            enemy->Start();
            enemy->skin.Location = enemyLoc;
        }
        
    }
    
    return nullptr;
}

void Field::End()
{
    entityManager->End();
    delete entityManager;
    user->End();
    delete user;
    player->End();
    delete player;
}