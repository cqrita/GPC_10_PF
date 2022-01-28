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
		speed = 800;
	}

	duration = 0;
}

void Missile::Update()
{
	this->moveUpdate();
	duration += Engine::Time::Get::Delta();
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
	Vector<2> direction = dMap1[this->direction];
	
	skin.Location += Normalize(direction) * speed * Engine::Time::Get::Delta();
}

Missile::Missile()
{
}

Missile::Missile(float angle, Vector<2> location, Dir direction)
{
	this->angle = angle;
	this->skin.Location = location;
	this->direction = direction;
}


