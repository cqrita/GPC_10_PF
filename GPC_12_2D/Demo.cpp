#include "Demo.h"
#include "User.h"
#include "Field.h"

void Demo::Start()
{
    Now = new Field;

    Now->Start();
}

void Demo::Update()
{
    Scene * const Next = Now->Update();

    if(Next != nullptr)
    {
        Now->End();

        delete Now;

        Now = Next;

        Now->Start();
    }
}

void Demo::End()
{
    Now->End();

    delete Now;
}