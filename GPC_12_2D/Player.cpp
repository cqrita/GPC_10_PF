#include "Player.h"

void Player::Start()
{
}

void Player::Update()
{
	for (Missile* m : missiles)
	{
		m->Update();
	}
}

void Player::End()
{
}
