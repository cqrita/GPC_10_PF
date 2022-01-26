#include "Player.h"
#include "Engine/Time.h"
void Player::Start()
{
    {
        skin.Name = "Animation/Sonic/Idle";
        skin.Duration = 1.0f;
        skin.Repeatable = true;

        skin.Length = Vector<2>(156, 160);
    }
    {
        body.Length = Point(100, 150);

        box.Name = "Image/GBB";
        box.Length = Vector<2>(100, 150);
    }
    {
        speed = 0;
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
	for (Missile* m : missiles)
	{
		m->Update();
	}
}

void Player::End()
{

}

void Player::createMissile()
{

}

void Player::changeMoveState(Dir direction, const char* state)
{
	this->direction = direction;
    if (state == "Run")
    {
        moveState = MoveState::run;
    }
    else if (state == "Move")
    {
        moveState = MoveState::move;
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
    else if (moveState == MoveState::move)
    {
        skin.Name = "Animation/Sonic/Move";
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
	skin.Location += direction * speed * Engine::Time::Get::Delta();
}


