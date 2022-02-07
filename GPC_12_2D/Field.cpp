#include <Windows.h>
#include <iostream>
#include "Field.h"
#include "Global.h"

#include "Engine/Input.h"
#include "Player.h"
#include "Enemy.h"

void Field::Start()
{
    {
        background.Name = "Image/Celadon";

        background.Length = Vector<2>(bkWidth, bkHeight)*2;
    }
    

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
    if (Input::Get::Key::Down(VK_RBUTTON))
    {
        Vector<2> enemyLoc = Vector<2>(user->camera.Location[0]+Input::Get::Cursor::X()-camWidth, user->camera.Location[1]+camHeight - Input::Get::Cursor::Y());
        
        Enemy* enemy = new Enemy();

        enemies.push_back(enemy);
        entityManager->addAgent(enemy);
        enemy->Start();
        enemy->skin.Location = enemyLoc;
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