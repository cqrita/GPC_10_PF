#include "Item.h"
#include "Global.h"
#include "Engine/Time.h"
#include <string>
void Item::Start()
{
    {
        skin.Name = "Animation/Chest/Chest";
        skin.Duration = 0.25f;
        skin.Repeatable = true;

        skin.Length = Vector<2>(10, 10) * 2;
    }
    {
        body.Length = Point(10 * 2, 10 * 2);
    }
    {
        state = 1;
    }
    {
        itemValue = static_cast<ItemValue>(rand()%static_cast<int>(ItemValue::Count));
        if (itemValue == ItemValue::Health)
        {
            itemNum = (rand() % 50)+1;
        }
        else if (itemValue == ItemValue::MissilePower)
        {
            itemNum = (rand() % 2)+1;

        }
    }
}

void Item::Update()
{
    {
        body.Center.x = skin.Location[0];
        body.Center.y = skin.Location[1];
    }
    {
        skin.Render();
       
    }
    {
        if (colState)
        {
            colDuration -= Engine::Time::Get::Delta();
        }
        if (colDuration < 0)
        {
            state = 0;
            this->End();
        }
    }
}

void Item::End()
{
    
}

void Item::getCam(Vector<2> location)
{
    cam = location;
}

void Item::onCollide()
{
    skin.Name = "Animation/Chest/ChestOpen";
    state = 2;
    colState = true;
}
