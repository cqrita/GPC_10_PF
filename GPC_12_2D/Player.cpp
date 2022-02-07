#include "Player.h"
#include "Engine/Time.h"
#include <iostream>
#include "Global.h"
#include <cmath>
void Player::Start()
{
    {
        skin.Name = "Animation/Sonic/Idle";
        skin.Duration = 1.0f;
        skin.Repeatable = true;

        skin.Length = Vector<2>(playerWidth, playerHeight)*2;
        skin.Location = Vector<2>(0, 0);
    }
    {
        body.Length = Point(playerWidth*2, playerHeight*2);

        box.Name = "Image/GBB";
        box.Length = Vector<2>(playerWidth, playerHeight) * 2;
    }
    {
        speed = 0;
        attackspeed=0.1f;
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
    
    if (attack)
    {
        attackspeed -= Engine::Time::Get::Delta();
    }
    if (attackspeed < 0)
    {
        attackspeed = 0.1f;
        attack = false;
    }
    {
        skin.Render();
        box.Render();
    }
    
	for (auto m=missiles.begin(); m != missiles.end()&&!missiles.empty();)
	{		
        if ((*m)->state== 1)
        {
            (*m)->Update();
            ++m;
        }
        else
        {
            (*m)->End();
            m=missiles.erase(m);
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

void Player::createMissile(float x, float y)
{
    if (attack==false)
    {
        Vector<2> mouse = {x- skin.Location[0],y-skin.Location[1] };
        float angle = atan2f(mouse[1],mouse[0])*( 180.0f/3.14159265f);
        std::cout << angle << std::endl;
        Vector<2> location = Normalize(mouse) * 30 + skin.Location;
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
    {
        Vector<2> location = skin.Location+Normalize(direction) * speed * Engine::Time::Get::Delta();
        int check = this->bkCollide(location);
        if (check == 3)
        {
            skin.Location = location;
        }
        else if (check == 1)
        {
            skin.Location[0] = location[0];
        }
        else if (check == 2)
        {
            skin.Location[1] = location[1];
        }        
    }	    
}

int Player::bkCollide(Vector<2> location)
{
    if (location[0] > (playerWidth - bkWidth) && location[0] < (bkWidth - playerWidth))
    {
        if (location[1] > (playerHeight - bkHeight) && location[1] < (bkHeight - playerHeight))
        {
            return 3;
        }
        else
        {
            return 1;
        }
    }
    else 
    {
        if (location[1] > (playerHeight - bkHeight) && location[1] < (bkHeight - playerHeight))
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }   
}


