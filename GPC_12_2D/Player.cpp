#include "Player.h"
#include "Engine/Time.h"
#include <iostream>
#include "Global.h"
#include <string>
#include <cmath>
#include "Melee.h"
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
    {
        health = 100;
    }
    {
        healthText.Font.Name = "Font/arial";
        healthText.Font.Size = 30;
        healthText.Length= Vector<2>(50, 50) * 2;
        auto healthString = std::to_string(health);
        healthText.Text = healthString.c_str();
        healthText.Location[0] = skin.Location[0] - cam[0] + camWidth + 30;
        healthText.Location[1] = -skin.Location[1] + cam[1] + camHeight + 80;
    }
    
}

void Player::Update()
{	
    this->moveUpdateM();
    {
        body.Center.x = skin.Location[0];
        body.Center.y = skin.Location[1];
        box.Location = skin.Location;
    }
    
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
        healthText.Location[0] = skin.Location[0] - cam[0] + camWidth + 30;
        healthText.Location[1] = -skin.Location[1] + cam[1] + camHeight + 80;
        auto healthString = std::to_string(health);
        healthText.Text = healthString.c_str();
        healthText.Render();
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

void Player::misCollide(Missile* missile)
{

}

void Player::entCollide(Agent* agent)
{
    if (health > 0)
    {
        health = health - 1;
    }
}
void Player::createMissile(float x, float y)
{
    if (attack==false)
    {
        Vector<2> mouse = {x- skin.Location[0],y-skin.Location[1] };
        float angle = atan2f(mouse[1],mouse[0])*( 180.0f/3.14159265f);
        
        Vector<2> location = Normalize(mouse) * 30 + skin.Location;
        Missile* missile = new Missile(angle, location, preDirection,mouse);
        missiles.push_back(missile);
        missile->Start();
        attack = true;
    }
}

void Player::createMelee(float x, float y)
{
    if (attack == false)
    {
        Vector<2> mouse = { x - skin.Location[0],y - skin.Location[1] };
        float angle = atan2f(mouse[1], mouse[0]) * (180.0f / 3.14159265f);

        Vector<2> location = Normalize(mouse) * 30 + skin.Location;
        Melee* missile = new Melee(angle, location, preDirection, mouse);
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


void Player::getCam(Vector<2> location)
{
    cam = location;
}

void Player::changeMoveStateM(float angle, const char* state)
{
    if (run)
    {
        moveState = MoveState::run;
    }
    else if (state == "Run" && runCool == false)
    {
        run = true;
        runCool = true;
        moveState = MoveState::run;
        this->preAngle = angle;
        this->angle = angle;
        
    }
    else if (state == "Walk" || (state == "Run" && runCool == true))
    {
        moveState = MoveState::walk;
        this->preAngle = angle;
        this->angle = angle;
    }
    else
    {
        moveState = MoveState::idle;
    }
}

void Player::moveUpdateM()
{
    float const radian = angle * (3.14159265f / 180.0f);
    Vector<2> direction = { cos(radian), sin(radian) };
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
        Vector<2> location = skin.Location + Normalize(direction) * speed * Engine::Time::Get::Delta();
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
