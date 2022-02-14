#include "Enemy.h"
#include <cmath>
#include "Engine/Time.h"
#include "Global.h"
#include <string>
void Enemy::Start()
{
    {
        skin.Name = "Animation/Sonic/Walk";
        skin.Duration = 1.0f;
        skin.Repeatable = true;

        skin.Length = Vector<2>(50, 66);
        skin.Location = Vector<2>(0, 0);
    }
    {
        body.Length = Point(50, 66);

        box.Name = "Image/GBB";
        box.Length = Vector<2>(50, 66);
    }
    {
        speed = 300;
        direction = Dir::I;
    }

    {
        health = 100;
    }
    
        
    {
        auto healthString = std::to_string(health);
        healthText.Font.Name = "Font/arial";
        healthText.Font.Size = 30;
        healthText.Length = Vector<2>(50, 50) * 2;
        healthText.Text = healthString.c_str();
        
        healthText.Location[0] = skin.Location[0] - cam[0] + camWidth + 30;
        healthText.Location[1] = -skin.Location[1] + cam[1] + camHeight + 80;
        
    }
    {
        healthImage.Name = "Image/Free";
        float health = this->health * 0.01f;
        healthImage.Length = Vector<2>(50 * health, 20);
        healthImage.Location[0] = skin.Location[0] + (50 * health) / 2 - 25;
        healthImage.Location[1] = skin.Location[1] - 40;
    }
    {
        state = 1;
    }
    {
        colDuration = colConst;
        colState = false;
    }

    {
        attackDuration = attackSpeed;
        attack = false;
    }
}

void Enemy::Update()
{
    if (colState)
    {
        colDuration -= Engine::Time::Get::Delta();
    }
    if (colDuration < 0)
    {
        colDuration = colConst;
        colState = false;
    }

    if (attack)
    {
        attackDuration -= Engine::Time::Get::Delta();
    }
    if (attackDuration < 0)
    {
        attackDuration = attackSpeed;
        attack = false;
    }



    {
        body.Center.x = skin.Location[0];
        body.Center.y = skin.Location[1];
        box.Location = skin.Location;
    }
    {
        healthText.Location[0] = skin.Location[0] - cam[0] + camWidth + 30;
        healthText.Location[1] = -skin.Location[1] + cam[1] + camHeight + 80;
        auto healthString = std::to_string(health);
        healthText.Text = healthString.c_str();
    }
    
    {
        skin.Render();
        box.Render();
    }
    {
        float health = this->health * 0.01f;
        healthImage.Length = Vector<2>(50 * health, 20);
        healthImage.Location[0] = skin.Location[0]+(50 * health)/2-25;
        healthImage.Location[1] = skin.Location[1] - 40;
        healthImage.Render();
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

void Enemy::End()
{
    this->~Enemy();
}

void Enemy::misCollide(Missile* missile)
{
    if (colState == false)
    {
        if (health > 0)
        {
            health = health - missile->damage;
        }
        if (health <= 0)
        {
            state = 0;
            this->End();
        }
        colState = true;
    }    
}

void Enemy::entCollide(Agent* agent)
{
    colState = true;
}

void Enemy::moveUpdate(Vector<2> location)
{
    float speed = this->speed;
    Vector<2> dir = location - skin.Location;
    float angle = atan2f(dir[1], dir[0]);
    if (colState)
    {
        speed = speed + 1000;
        angle = angle + (3.14159265f);
    }

    Vector<2> direction = { cos(angle), sin(angle) };
    if (direction[0] < 0)
    {
        skin.Flipped = true;
        if (colState)
        {
            skin.Flipped = false;
        }
    }
    else
    {
        skin.Flipped = false;
        if (colState)
        {
            skin.Flipped = true;
        }
    }
    skin.Location += Normalize(direction) * speed * Engine::Time::Get::Delta();
    createMissile(location[0], location[1]);
}


void Enemy::getCam(Vector<2> location)
{
    cam = location;
}

void Enemy::createMissile(float x, float y)
{
    if (attack == false)
    {
        Vector<2> mouse = { x - skin.Location[0],y - skin.Location[1] };
        float angle = atan2f(mouse[1], mouse[0]) * (180.0f / 3.14159265f);

        Vector<2> location = Normalize(mouse) * 30 + skin.Location;
        Missile* missile = new Missile(angle, location, mouse);
        missiles.push_back(missile);
        missile->Start();
        attack = true;
    }
}
