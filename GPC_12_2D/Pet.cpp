#include "Pet.h"
#include "Engine/Time.h"
#include "PetMissile.h"
void Pet::Start()
{
    {
        skin.Name = "Animation/Rabbit/Run";
        skin.Duration = 0.25f;
        skin.Repeatable = true;

        skin.Length = Vector<2>(40, 55);
    }
    
    {
        speed = 300;
    }
    {
        angle = 0;
    }
}

void Pet::Update()
{
    if (this->angle <= 3.14159265f*2)
    {
        this->angle += Engine::Time::Get::Delta()*2;
    }
    else
    {
        this->angle = 0;
    }
    this->moveUpdate();

    if (attack)
    {
        attackDuration -= Engine::Time::Get::Delta();
    }
    if (attackDuration < 0)
    {
        attackDuration = attackSpeed;
        attack = false;
        enemy = Vector<2>(5000, 5000);
    }
    {
        skin.Render();
    }

    for (auto m = missiles.begin(); m != missiles.end() && !missiles.empty();)
    {
        if ((*m)->state == 1)
        {
            (*m)->Update();
            ++m;
        }
        else
        {
            (*m)->End();
            m = missiles.erase(m);
        }
    }
}

void Pet::End()
{
    for (auto m = missiles.begin(); m != missiles.end() && !missiles.empty();)
    {
        (*m)->End();
        m = missiles.erase(m);
    }
}

void Pet::moveUpdate()
{
    player[0] = player[0] - 100;
    Vector<2> dir = player - skin.Location;
    
    float angle = atan2f(dir[1], dir[0]);
    Vector<2> direction = { cos(angle), sin(angle) };
    if (Length(dir) > 5.0f)
    {
        if (direction[0] < 0)
        {
            skin.Flipped = false;
        }
        else
        {
            skin.Flipped = true;
        }
    }
    skin.Location += Normalize(direction) * speed * Engine::Time::Get::Delta();       
}

void Pet::getCam(Vector<2> location)
{
    cam = location;
}

void Pet::createMissile(float x, float y)
{
    if (attack == false)
    {
        Vector<2> mouse = { x - skin.Location[0],y - skin.Location[1] };
        float angle = atan2f(mouse[1], mouse[0]) * (180.0f / 3.14159265f);

        Vector<2> location = Normalize(mouse) * 30 + skin.Location;
        PetMissile* missile = new PetMissile(angle, location, mouse);
        missiles.push_back(missile);
        missile->Start();
        attack = true;
    }
}

void Pet::getEnemy(Vector<2> location)
{
    if (Length(skin.Location - enemy) > Length(skin.Location - location))
    {
        enemy = location;       
    }
    if (Length(skin.Location - enemy) < 400)
    {
        this->createMissile(location[0], location[1]);
    }
}

void Pet::getPlayer(Vector<2> location)
{
    player = location;
}
