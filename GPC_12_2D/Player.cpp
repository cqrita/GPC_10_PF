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
        skin.Name = "Animation/Black/Idle";
        skin.Duration = 0.25f;
        skin.Repeatable = true;

        skin.Length = Vector<2>(playerWidth, playerHeight)*2;
        skin.Location = Vector<2>(0, 0);
    }
    {
        body.Length = Point(playerWidth*2-10, playerHeight*2-10);

        box.Name = "Image/GBB";
        box.Length = Vector<2>(playerWidth, playerHeight) * 2-Vector<2>(10,10);
    }
    {
        speed = 0;
        attackDuration = attackConst/attackSpeed;
        runDuration = runConst;
        attackTime = false;
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
    {
        colDuration = colConst;
        colState = false;
    }
    {
        petNum = 1;
    }
    {
        muzzle.Name = "Animation/Black/MuzzleFlash";
        muzzle.Duration = 0.1f;
        muzzle.Repeatable = true;

        muzzle.Length = Vector<2>(0, 0);
        muzzle.Location = Vector<2>(0, 0);
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
}

void Player::Update()
{	
    this->moveUpdateM();
    this->createPet();
    {
        body.Center.x = skin.Location[0];
        body.Center.y = skin.Location[1];
        box.Location = skin.Location;
    }
    
    if (attackTime)
    {
        attackDuration -= Engine::Time::Get::Delta();
    }
    if (attackDuration < 0)
    {
        attackDuration = attackConst / attackSpeed;
        attackTime = false;
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

    if (colState)
    {
        colDuration -= Engine::Time::Get::Delta();
    }
    if (colDuration < 0)
    {
        colDuration = colConst;
        colState = false;
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
        muzzle.Render();
        muzzle.Length = Vector<2>(0, 0);
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
    for (auto p = pets.begin(); p != pets.end() && !pets.empty();)
    {
        (*p)->getPlayer(skin.Location);
        (*p)->Update();
        ++p;                
    }

    attack = false;
}

void Player::End()
{
    for (auto m = missiles.begin(); m != missiles.end() && !missiles.empty();)
    {        
        (*m)->End();
        m = missiles.erase(m);        
    }
    for (auto p = pets.begin(); p != pets.end() && !pets.empty();)
    {
        (*p)->End();
        p = pets.erase(p);
    }
}

void Player::misCollide(Missile* missile)
{
    if (colState == false)
    {
        if (health > 0)
        {
            health = health - 1;
        }
        colState = true;
    }
}

void Player::entCollide(Agent* agent)
{
    if (colState == false)
    {
        if (health > 0)
        {
            health = health - 1;
        }
        colState = true;
    }
}
void Player::createMissile(float x, float y)
{
    muzzle.Length = Vector<2>(10, 10);
    attack = true;
    if (attackTime ==false)
    {
        Vector<2> mouse = {x- skin.Location[0],y-skin.Location[1] };
        float angle = atan2f(mouse[1],mouse[0])*( 180.0f/3.14159265f);
        if (mouse[0] > 0)
        {
            skin.Flipped = false;
        }
        else
        {
            skin.Flipped = true;
        }
        Vector<2> location = Normalize(mouse) * 25 + skin.Location;
        Missile* missile = new Missile(angle, location,mouse);
        missiles.push_back(missile);
        missile->Start();
        attackTime = true;

        muzzle.Location = Normalize(Vector<2>(mouse[0], 0)) * 20 + skin.Location;
    }
}

void Player::createMelee(float x, float y)
{
    muzzle.Length = Vector<2>(10, 10);
    attack = true;
    if (attackTime == false)
    {
        Vector<2> mouse = { x - skin.Location[0],y - skin.Location[1] };
        float angle = atan2f(mouse[1], mouse[0]) * (180.0f / 3.14159265f);
        if (mouse[0] > 0)
        {
            skin.Flipped = false;
        }
        else
        {
            skin.Flipped = true;
        }
        Vector<2> location = Normalize(mouse) * 30 + skin.Location;
        Melee* missile = new Melee(angle, location, mouse);
        missiles.push_back(missile);
        missile->Start();
        attackTime = true;

        
        muzzle.Location = Normalize(Vector<2>(mouse[0],0)) * 20 + skin.Location;
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
        skin.Name = "Animation/Black/Run";
        skin.Duration = 0.25f;
        speed = runSpeed;
    }
    else if (moveState == MoveState::walk)
    {
        skin.Name = "Animation/Black/Run";
        skin.Duration = 1.0f;
        speed = walkSpeed;
    }
    else
    {
        skin.Name = "Animation/Black/Idle";
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
    if (location[0] > (playerWidth - bkWidth-5) && location[0] < (bkWidth - playerWidth + 5))
    {
        if (location[1] > (playerHeight - bkHeight - 5) && location[1] < (bkHeight - playerHeight + 5))
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
        if (location[1] > (playerHeight - bkHeight - 5) && location[1] < (bkHeight - playerHeight + 5))
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
    skin.Repeatable = true;
    if (moveState == MoveState::run)
    {
        skin.Name = "Animation/Black/Run";
        skin.Duration = 0.1f;
        speed = runSpeed;
    }
    else if (moveState == MoveState::walk)
    {        
        skin.Name = "Animation/Black/Run";              
        skin.Duration = 0.5f;
        speed = walkSpeed;
    }
    else
    {
        if (attack)
        {
            skin.Name = "Animation/Black/Crouch";
            skin.Repeatable = false;
            skin.Playback = 0.4f;
        }
        else
        {
            skin.Name = "Animation/Black/Idle";
        }       
        skin.Duration = 0.5f;
        speed = 0;
    }
    if (attack == false && moveState != MoveState::idle)
    {
        if (direction[0] < 0)
        {
            skin.Flipped = true;
        }
        else if (direction[0] > 0)
        {
            skin.Flipped = false;
        }
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

void Player::createPet()
{
    if (pets.size()<petNum)
    {
        Vector<2> location = skin.Location;
        location[0] = location[0] + 100;
        Pet* pet = new Pet();
        pet->skin.Location = location;
        pets.push_back(pet);
        pet->Start();
    }
}
