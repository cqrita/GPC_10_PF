#include <Windows.h>

#include "Field.h"


#include "Engine/Input.h"
#include "Player.h"

void Field::Start()
{
    {
        background.Name = "Image/Celadon";

        background.Length = Vector<2>(960, 703) * 4;
    }
    

    {
        entityManager = new EntityManager;
        user = new User;
        player = new Player;        
        user->Start();
        entityManager->Start();
        player->Start();
        user->getPlayer(player);
    }
}

Scene* Field::Update()
{
    using namespace Engine;
    
    background.Render();
    entityManager->Update();
    user->Update();
    
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