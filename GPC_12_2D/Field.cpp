#include <Windows.h>
#include <iostream>
#include "Field.h"
#include "Global.h"
#include <cstdlib>
#include "Engine/Input.h"
#include "Player.h"
#include "Mushroom.h"
#include "Goblin.h"
#include "GameEnd.h"
#include <string>
void Field::Start()
{
    {
        background.Name = "Image/grass";

        background.Length = Vector<2>(bkWidth, bkHeight)*2;
    }
    {
        enemyCount = 0;
        UI.Font.Name = "Font/arial";
        UI.Font.Size = 30;
        UI.Length = Vector<2>(50, 50) * 2;
        UI.Location[0] = 100;
        UI.Location[1] = 100;
        auto countStr = std::to_string(enemyCount);
        UI.Text = countStr.c_str();
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
        user->getEntityManager(entityManager);
        entityManager->addPlayer(player);
    }
}

Scene* Field::Update()
{
    using namespace Engine;
    
    
    

    background.Render();
    
    
    if (enemies.size()<5)
    {
        int x = rand() % (bkWidth*2)- bkWidth;
        int y = rand() % (bkHeight*2)-bkHeight;
        if (!((x > user->camera.Location[0] - camWidth && x < user->camera.Location[0] + camWidth) && (y > user->camera.Location[1] - camHeight && y < user->camera.Location[1] + camHeight)))
        {
            Vector<2> enemyLoc = Vector<2>(x, y);
            int a = rand() % 2;
            if (a == 0)
            {
                Mushroom* enemy = new Mushroom();
                enemies.push_back(enemy);
                entityManager->addEnemy(enemy);
                enemy->Start();
                enemy->skin.Location = enemyLoc;
            }
            else
            {
                Goblin* enemy = new Goblin();
                enemies.push_back(enemy);
                entityManager->addEnemy(enemy);
                enemy->Start();
                enemy->skin.Location = enemyLoc;
            }            
        }        
    }
    for (auto e = enemies.begin(); e != enemies.end() && !enemies.empty();)
    {
        if ((*e)->state == 1)
        {
            (*e)->moveUpdate(player->skin.Location);
            (*e)->getCam(user->camera.Location);
            (*e)->Update();
            if ((*e)->deathState && !(*e)->exp)
            {
                player->getExp(1);
                (*e)->exp = true;
            }
            ++e;
            
        }
        else
        {
            Item* item = new Item();
            items.push_back(item);
            entityManager->addItem(item);
            item->skin.Location = (*e)->skin.Location;
            item->Start();
            
            (*e)->End();
            e = enemies.erase(e);
            enemyCount = enemyCount + 1;
        }
    }

    if (items.size() < 3)
    {
        int x = rand() % (bkWidth * 2) - bkWidth;
        int y = rand() % (bkHeight * 2) - bkHeight;
        if (!((x > user->camera.Location[0] - camWidth && x < user->camera.Location[0] + camWidth) && (y > user->camera.Location[1] - camHeight && y < user->camera.Location[1] + camHeight)))
        {
            Vector<2> itemLoc = Vector<2>(x, y);
            Item* item = new Item();
            items.push_back(item);
            entityManager->addItem(item);
            item->skin.Location = itemLoc;
            item->Start();
        }
    }
    for (auto e = items.begin(); e != items.end() && !items.empty();)
    {
        if ((*e)->state > 0)
        {                       
            if (items.size() > 15)
            {
                (*e)->End();
                e = items.erase(e);
            }
            else
            {
                (*e)->getCam(user->camera.Location);
                (*e)->Update();
                ++e;
            }
            
        }
        else
        {
            (*e)->End();
            e = items.erase(e);
        }
    }





    entityManager->Update();
    user->Update();

    {
        UI.Location[0] = 100;
        UI.Location[1] = 100;
        auto countStr = std::to_string(enemyCount);
        UI.Text = countStr.c_str();
        UI.Render();
    }
    if (player->state == 0)
    {
        return new GameEnd(enemyCount);
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