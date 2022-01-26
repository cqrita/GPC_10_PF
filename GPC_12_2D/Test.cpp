#include <Windows.h>

#include "Test.h"
#include "Test2.h"

#include "Engine/Input.h"
#include "Dummy.h"

void Test::Start()
{
    {
        Background.Name = "Image/Celadon";

        Background.Length = Vector<2>(960, 703) * 4;
    }
    {
        Player = new Dummy;

        Player->Start();
    }
}

Scene * Test::Update()
{
    using namespace Engine;

    Background.Render();

    
    
    Free.Skin.Render();

    Player->Update();

    return nullptr;
}

void Test::End()
{
    Player->End();

    delete Player;
}