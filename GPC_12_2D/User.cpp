#include "User.h"
#include "Engine/Input.h"
#include "Engine/Time.h"
#include "Engine/Vector.h"
#include "Direction.h"
void User::Start()
{

}

void User::Update()
{
    this->checkInput();
    this->dummy.Update();
    {
        
    }
}

void User::End()
{

}

void User::checkInput()
{
    using namespace Engine;
    Vector<2> direction = Vector<2>();
    const char* state;
    if(
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

    if (
        not Input::Get::Key::Press('A') and
        not Input::Get::Key::Press('D') and
        not Input::Get::Key::Press('W') and
        not Input::Get::Key::Press('S')
        )
    {
        state = "Idle";
    }
     
    if (Input::Get::Key::Press('A')) direction += { -1, 0 };
    if (Input::Get::Key::Press('D')) direction += { +1, 0 };
    if (Input::Get::Key::Press('W')) direction += {  0, +1 };
    if (Input::Get::Key::Press('S')) direction += {  0, -1 };

}
