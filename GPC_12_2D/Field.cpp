#include <Windows.h>
#include <iostream>
#include "Field.h"
#include "Global.h"
#include <cstdlib>
#include "Engine/Input.h"
#include "Engine/Time.h"
#include "Player.h"
#include "Mushroom.h"
#include "Goblin.h"
#include "FlyingEye.h"
#include "GameEnd.h"
#include "LevelManager.h"
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
    {
        stage = 1;
    }
    std::srand(static_cast<unsigned int>(time(nullptr)));
    {
        entityManager = new EntityManager;
        user = new User;
        player = new Player;
        levelManager = new LevelManager;
        user->Start();
        entityManager->Start();
        player->Start();
        user->getPlayer(player);
        user->getEntityManager(entityManager);
        entityManager->addPlayer(player);
        levelManager->setLevel(stage);
    }
    {
        battle.Name = "Sound/Battle";
        battle.Volume = -1000;
        battle.Start();
        battle.Music();
    }
    {
        stageDuration = stageConst;
    }
}

Scene* Field::Update()
{
    using namespace Engine;
    
    
    stageDuration -= Engine::Time::Get::Delta();   
    if (stageDuration < 0)
    {
        stageDuration = stageConst;
        stage++;
        levelManager->setLevel(stage);
    }

    background.Render();
    
    levelManager->setEnemSize(enemies.size());
    Enemy* enemy = levelManager->getEnemies();
    if (enemy != nullptr)
    {
        entityManager->addEnemy(enemy);
        enemy->Start();
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

    levelManager->setItemSize(items.size());
    Item* item = levelManager->getItems();
    if (item != nullptr)
    {
        items.push_back(item);
        entityManager->addItem(item);
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
    battle.Stop();
    battle.End();
    entityManager->End();
    delete levelManager;
    delete entityManager;
    user->End();
    delete user;
    player->End();
    delete player;
}