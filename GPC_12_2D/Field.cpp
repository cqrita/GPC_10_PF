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
        player = new Player;
        player->Start();
    }
}

Scene* Field::Update()
{
    using namespace Engine;

    background.Render();



    return nullptr;
}

void Field::End()
{
    player->End();
    delete player;
}