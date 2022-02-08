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
        attackDuration = attackConst/attackSpeed;
        runDuration = runConst;
        attack = false;
        run = false;
        runCool = false;
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
    std::cout << skin.Location[0] <<" " << skin.Location[1] << std::endl;
    if (attack)
    {
        attackDuration -= Engine::Time::Get::Delta();
    }
    if (attackDuration < 0)
    {
        attackDuration = attackConst / attackSpeed;
        attack = false;
    }

    if(run)
    {
        runDuration -= Engine::Time::Get::Delta();
    }
    if (runDuration < 0)
    {
        runDuration = runConst;
        run = false;
    }
    
    if (runCool)
    {
        runCoolDuration -= Engine::Time::Get::Delta();
    }
    if (runCoolDuration < 0)
    {
        runCoolDuration = runCooltime;
        runCool = false;
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
        
        Vector<2> location = Normalize(mouse) * 30 + skin.Location;
        Missile* missile = new Missile(angle, location, preDirection);
        missiles.push_back(missile);
        missile->Start();
        attack = true;
    }
}

void Player::changeMoveState(Dir direction, const char* state)
{
    if (run)
    {
        moveState = MoveState::run;
    }
    else if (state == "Run"&&runCool==false)
    {
        run = true;
        runCool = true;
        moveState = MoveState::run;
        this->preDirection = direction;
        this->direction = direction;
    }
    else if (state == "Walk"||(state == "Run" && runCool == true))
    {
        moveState = MoveState::walk;
        this->preDirection = direction;
        this->direction = direction;
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
        speed = runSpeed;
    }
    else if (moveState == MoveState::walk)
    {
        skin.Name = "Animation/Sonic/Walk";
        skin.Duration = 1.0f;
        speed = walkSpeed;
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


