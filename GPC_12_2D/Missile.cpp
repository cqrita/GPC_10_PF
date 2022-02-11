#include "Missile.h"
#include "Engine/Time.h"
#include <iostream>
void Missile::Start()
{
	{
		skin.Name = "Animation/Sonic/Idle";;
		

		skin.Length = Vector<2>(20, 20);
		
	}
	{
		body.Radius = skin.Length[0] / 2;
		body.Center = Point(skin.Location[0], skin.Location[1]);

		box.Name = "Image/GBB";
		box.Length = Vector<2>(20, 20);

	}


	{
		speed = 1000;
	}
	{
		EnemyHoming = false;
	}
	duration = 0;
}

void Missile::Update()
{
	this->moveUpdate();
	duration += Engine::Time::Get::Delta();
	if (distance > 500 || duration > 1000)
	{
		state = 0;
	}
	{
		body.Center.x = skin.Location[0];
		body.Center.y = skin.Location[1];
		box.Location = skin.Location;
	}
	{
		skin.Render();
		box.Render();
	}
	
	
}

void Missile::End()
{
	this->~Missile();
}

void Missile::moveUpdate()
{
	float angle = this->angle;
	if (EnemyHoming)
	{
		angle=this->changeAngle();
		EnemyHoming = false;
	}
	float const radian = angle * (3.14159265f / 180.0f);
	Vector<2> direction={cos(radian), sin(radian)};
	Vector<2> dist = Normalize(direction) * speed * Engine::Time::Get::Delta();
	distance += Length(dist);
	skin.Location += dist;
	if (angle >= 90 && angle <= 180)
	{
		skin.Angle = angle-180;
		skin.Flipped = true;
	}
	else if(angle <= -90 && angle >= -180)
	{
		skin.Angle = angle+180;
		skin.Flipped = true;
	}
	else
	{
	skin.Angle = angle;
	skin.Flipped = false;
	}
}

void Missile::getEnemy(Vector<2> location)
{
	if (Length(skin.Location - enemy) > Length(skin.Location - location)&& Length(skin.Location - location)<400)
	{
		enemy = location;
		EnemyHoming = true;
	}	
}

float Missile::changeAngle()
{
	Vector<2> loc = { enemy[0] - skin.Location[0],enemy[1] - skin.Location[1] };
	return atan2f(loc[1], loc[0]) * (180.0f / 3.14159265f);
}

Missile::Missile()
{

}

Missile::~Missile()
{
	
}

Missile::Missile(float angle, Vector<2> location, Dir direction, Vector<2> user)
{
	this->angle = angle;
	this->skin.Location = location;
	this->direction = direction;
	this->enemy = user;
}


