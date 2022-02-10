#include "Enemy.h"
#include <cmath>
#include "Engine/Time.h"
#include "Global.h"
void Enemy::Start()
{
    {
        skin.Name = "Animation/Sonic/Idle";
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
        healthText.Font.Name = "Font/arial";
        healthText.Font.Size = 30;
        healthText.Length = Vector<2>(50, 50) * 2;
        healthText.Text = "test";
        
        healthText.Location[0] = skin.Location[0] - cam[0] + camWidth + 30;
        healthText.Location[1] = -skin.Location[1] + cam[1] + camHeight + 80;
        
    }
    {
        state = 1;
    }
}

void Enemy::Update()
{
    {
        body.Center.x = skin.Location[0];
        body.Center.y = skin.Location[1];
        box.Location = skin.Location;
    }
    {
        healthText.Location[0] = skin.Location[0] - cam[0] + camWidth + 30;
        healthText.Location[1] = -skin.Location[1] + cam[1] + camHeight + 80;
    }
    {
        healthText.Render();
        skin.Render();
        box.Render();
    }
}

void Enemy::End()
{
    this->~Enemy();
}

void Enemy::misCollide()
{
    state = 0;
    this->End();
}

void Enemy::entCollide()
{

}

void Enemy::moveUpdate(Vector<2> location)
{
    Vector<2> dir = location - skin.Location ;
    float angle = atan2f(dir[1], dir[0]);   
    Vector<2> direction = { cos(angle), sin(angle) };
    skin.Location += Normalize(direction) * speed * Engine::Time::Get::Delta();    
}

void Enemy::getCam(Vector<2> location)
{
    cam = location;
}
