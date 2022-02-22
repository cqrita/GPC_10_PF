#include "User.h"
#include "Engine/Input.h"
#include "Engine/Time.h"
#include <iostream>
#include <Windows.h>
#include "Global.h"

void User::Start()
{    
    this->camera.Sight = Vector<2>(camWidth, camHeight)*2;   

    {
        doubleTap = 0.05f;
        doubleTapFlag = false;
    }
}

void User::Update()
{
    
    if (doubleTapFlag)
    {
        doubleTap -= Engine::Time::Get::Delta();
    }
    if (doubleTap < 0)
    {
        doubleTap = doubleTapConst;
        doubleTapFlag = false;
    }
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
    this->player->getCam(camera.Location);
    this->player->Update();
    
}

void User::End()
{

}

void User::checkInput()
{
    this->moveInputM();
    this->attackInput();
    this->meleeInput();
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
        if (Input::Get::Key::Down(VK_SPACE))
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
        int a=0;
    }
}

void User::meleeInput()
{
    if (Input::Get::Key::Press(VK_RBUTTON))
    {
        auto value = entityManager->mouseCollision(getMouseX(),getMouseY());
        if (value.flag == true && Length(player->skin.Location-value.location)<150)
        {
            player->createMelee(getMouseX(), getMouseY());
        }
    }
}

void User::getPlayer(Player* player)
{
    this->player = player;
}

void User::getEntityManager(EntityManager* entityManager)
{
    this->entityManager = entityManager;
}


float User::getMouseX()
{
    return camera.Location[0] + Input::Get::Cursor::X() - camWidth;
}

float User::getMouseY()
{
    return camera.Location[1] + camHeight - Input::Get::Cursor::Y();
}

void User::moveInputM()
{
    using namespace Engine;
    const char* state = "";
    if (Input::Get::Key::Press(VK_RBUTTON))
    {
        if (Input::Get::Key::Down(VK_SPACE))
        {
            state = "Run";
        }
        else
        {
            state = "Walk";
        }
    }
    else
    {
        state = "Idle";
    }
    
    Vector<2> mouse = { getMouseX() - player->skin.Location[0],getMouseY() - player->skin.Location[1] };
    float angle = atan2f(mouse[1], mouse[0]) * (180.0f / 3.14159265f);    
    player->changeMoveStateM(angle, state);
}

