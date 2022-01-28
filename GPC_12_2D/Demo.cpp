#include "Demo.h"
#include "Field.h"
#include "Test.h"
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
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