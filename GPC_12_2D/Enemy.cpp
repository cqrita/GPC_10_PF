#include "Enemy.h"
#include <cmath>
#include "Engine/Time.h"
#include "Global.h"
#include <string>
#include <iostream>
void Enemy::Start()
{
    {
        skin.Name = "Animation/Mushroom/Run";
        skin.Duration = 0.5f;
        skin.Repeatable = true;

        skin.Length = Vector<2>(50, 50)*4;
    }
    {
        body.Length = Point(40, 40);

        box.Name = "Image/GBB";
        box.Length = Vector<2>(50, 66);
    }
    {
        constSpeed = 300;
        direction = Dir::I;
    }

    {
        health = 100;
    }
    {
        bar.Name = "Image/Bar";
        bar.Length = Vector<2>(60, 10);
        bar.Location[0] = skin.Location[0];
        bar.Location[1] = skin.Location[1] - 40;
    }
    {
        progressBar.Name = "Image/ProgressBar";
        float health = this->health * 0.01f;
        progressBar.Length = Vector<2>(60 * health, 10);
        progressBar.Location[0] = skin.Location[0] + (60 * health) / 2 - 30;
        progressBar.Location[1] = skin.Location[1] - 40;
    }
    {
        barBorder.Name = "Image/ProgressBarBorder";
        barBorder.Length = Vector<2>(60, 10);
        barBorder.Location[0] = skin.Location[0];
        barBorder.Location[1] = skin.Location[1] - 40;
    }
    {
        state = 1;
    }
    {
        colDuration = colConst;
        colState = false;
    }

    {
        attackCool = attackSpeed;
        attackCoolFlag = false;
    }
    {
        attackDuration = attackTime;
        attack = false;
    }
}

void Enemy::Update()
{
    if (!attack)
    {
        this->move();
        skin.Name = "Animation/Mushroom/Run";
    }
    else if (colState)
    {
        this->move();
        skin.Name = "Animation/Mushroom/Attack";
    }
    else
    {
        skin.Name = "Animation/Mushroom/Attack";
    }
    if (attackCoolFlag == false)
    {

        attackCoolFlag = true;
        attack = true;
    }
    
    
    if (colState)
    {
        colDuration -= Engine::Time::Get::Delta();
    }
    if (colDuration < 0)
    {
        colDuration = colConst;
        colState = false;
    }

    if (attackCoolFlag)
    {
        attackCool -= Engine::Time::Get::Delta();
    }
    if (attackCool < 0)
    {
        attackCool = attackSpeed;
        attackCoolFlag = false;
    }

    if (attack)
    {
        attackDuration -= Engine::Time::Get::Delta();
    }
    if (attackDuration < 0)
    {
        this->createMissile(player[0], player[1]);
        attackDuration = attackTime;
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
    }
    {
        bar.Location[0] = skin.Location[0];
        bar.Location[1] = skin.Location[1] - 40;
        bar.Render();
    }
    {
        float health = this->health * 0.01f;
        progressBar.Length = Vector<2>(60 * health, 10);
        progressBar.Location[0] = skin.Location[0] + (60 * health) / 2 - 30;
        progressBar.Location[1] = skin.Location[1] - 40;
        progressBar.Render();
    }
    {
        barBorder.Location[0] = skin.Location[0];
        barBorder.Location[1] = skin.Location[1] - 40;
        barBorder.Render();
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
    for (auto m = missiles.begin(); m != missiles.end() && !missiles.empty();)
    {
        (*m)->End();
        m = missiles.erase(m);
    }
    this->~Enemy();
}

void Enemy::misCollide(Missile* missile)
{
    std::cout << "collided" << std::endl;
    
    if (health > 0)
    {
        health = health - missile->damage;
    }
    if (health <= 0)
    {
        state = 0;
        this->End();
    }
        
}

void Enemy::entCollide(Agent* agent)
{
    colState = true;
}

void Enemy::moveUpdate(Vector<2> location)
{
    player = location;
    speed = constSpeed;
    Vector<2> dir = location - skin.Location;
    angle = atan2f(dir[1], dir[0]);
    if (colState)
    {
        speed = 0;
        angle = angle + (3.14159265f);
    }   
}

void Enemy::move()
{
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
}


void Enemy::getCam(Vector<2> location)
{
    cam = location;
}

void Enemy::createMissile(float x, float y)
{   
    Vector<2> mouse = { x - skin.Location[0],y - skin.Location[1] };
    float angle = atan2f(mouse[1], mouse[0]) * (180.0f / 3.14159265f);

    Vector<2> location = Normalize(mouse) * 30 + skin.Location;
    Missile* missile = new Missile(angle, location, mouse);
    missiles.push_back(missile);
    missile->Start();
}

