#include "Player.h"
#include "Engine/Time.h"
#include <iostream>
void Player::Start()
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
        speed = 0;
        attackspeed=0.2f;
        attack = false;
        direction = Dir::I;
    }
}

void Player::Update()
{	
    this->moveUpdate();
    {
        body.Center.x = skin.Location[0];
        body.Center.y = skin.Location[1];
        box.Location = skin.Location;
    }
    {
        skin.Render();
        box.Render();
    }
    if (attack)
    {
        attackspeed -= Engine::Time::Get::Delta();
    }
    if (attackspeed < 0)
    {
        attackspeed = 0.2f;
        attack = false;
    }
    std::cout << skin.Location[0] <<" " <<skin.Location[1]<< std::endl;
	for (Missile* m : missiles)
	{		
        if (m->duration < 0.5)
        {
            m->Update();
        }
        else
        {
            m->End();
        }
	}
}

void Player::End()
{

}

void Player::misCollide()
{

}

void Player::entCollide()
{

}

void Player::createMissile()
{
    if (attack==false)
    {
        float angle = dMap3[preDirection];
        Vector<2> location = dMap1[preDirection] * 30 + skin.Location;
        Missile* missile = new Missile(angle, location, preDirection);
        missiles.push_back(missile);
        missile->Start();
        attack = true;
    }
}

void Player::changeMoveState(Dir direction, const char* state)
{
	this->direction = direction;
    
    if (state == "Run")
    {
        moveState = MoveState::run;
        this->preDirection = direction;
    }
    else if (state == "Walk")
    {
        moveState = MoveState::walk;
        this->preDirection = direction;
    }
    else
    {
        moveState = MoveState::idle;
    }
    
}

void Player::moveUpdate()
{
	Vector<2> direction = dMap1[this->direction];
    
    if (moveState == MoveState::run)
    {
        skin.Name = "Animation/Sonic/Run";
        skin.Duration = 0.25f;
        speed = 600;
    }
    else if (moveState == MoveState::walk)
    {
        skin.Name = "Animation/Sonic/Walk";
        skin.Duration = 1.0f;
        speed = 300;
    }
    else
    {
        skin.Name = "Animation/Sonic/Idle";
        skin.Duration = 1.0f;
        speed = 0;
    }
    if (direction[0] < 0)
    {
        skin.Flipped = true;
    }
    else if (direction[0] > 0)
    {
        skin.Flipped = false;
    }
    if (direction[0] != 0 or direction[1] != 0)
	    skin.Location += Normalize(direction) * speed * Engine::Time::Get::Delta();
    
   
}


