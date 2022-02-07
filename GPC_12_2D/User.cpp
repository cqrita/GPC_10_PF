#include "User.h"
#include "Engine/Input.h"
#include <iostream>
#include <Windows.h>
#include "Global.h"

void User::Start()
{    
    this->camera.Sight = Vector<2>(camWidth, camHeight)*2;   
}

void User::Update()
{
    this->checkInput();
    if (player->skin.Location[0] > (camWidth - bkWidth) && player->skin.Location[0] < (bkWidth - camWidth))
    {
        this->camera.Location[0] = player->skin.Location[0];
    }
    if (player->skin.Location[1] > (camHeight - bkHeight) && player->skin.Location[1] < (bkHeight - camHeight))
    {
        this->camera.Location[1] = player->skin.Location[1];
    }
    this->camera.Set();
    this->player->Update();
    
}

void User::End()
{

}

void User::checkInput()
{
    this->moveInput();
    this->attackInput();
}

void User::moveInput()
{
    using namespace Engine;
    Vector<2> direction = Vector<2>();
    const char* state="";
    if (
        Input::Get::Key::Press('A') or
        Input::Get::Key::Press('D') or
        Input::Get::Key::Press('W') or
        Input::Get::Key::Press('S')
        )
    {
        if (Input::Get::Key::Press('E'))
        {
            state = "Run";
        }
        else
        {
            state = "Walk";
        }
    }

    if (Input::Get::Key::Press('A')) direction += { -1, 0 };
    if (Input::Get::Key::Press('D')) direction += { +1, 0 };
    if (Input::Get::Key::Press('W')) direction += {  0, +1 };
    if (Input::Get::Key::Press('S')) direction += {  0, -1 };
    if (direction[0] == 0 && direction[1] == 0)
    {
        state = "Idle";
    }
    std::array<float, 2>arr = { direction[0], direction[1] };
    player->changeMoveState(dMap2[arr], state);
}

void User::attackInput()
{
    using namespace Engine;
    if (Input::Get::Key::Press(VK_LBUTTON))
    {
        player->createMissile(getMouseX(),getMouseY());
    }
}

void User::getPlayer(Player* player)
{
    this->player = player;
}

float User::getMouseX()
{
    return camera.Location[0] + Input::Get::Cursor::X() - camWidth;
}

float User::getMouseY()
{
    return camera.Location[1] + camHeight - Input::Get::Cursor::Y();
}

