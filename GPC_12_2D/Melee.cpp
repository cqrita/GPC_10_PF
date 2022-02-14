#include "Melee.h"
#include "Engine/Time.h"
void Melee::Start()
{
	{
		skin.Name = "Animation/Fio";


		skin.Length = Vector<2>(50, 50);

	}
	{
		body.Radius = skin.Length[0] / 2;
		body.Center = Point(skin.Location[0], skin.Location[1]);

		box.Name = "Image/GBB";
		box.Length = Vector<2>(50, 50);

	}


	{
		speed = 250;
		damage = 20;
	}
	{
		EnemyHoming = false;
	}
	duration = 0;
}

void Melee::Update()
{
	this->moveUpdate();
	duration += Engine::Time::Get::Delta();
	if (distance > 100 || duration > 2000)
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

Melee::Melee(float angle, Vector<2> location, Vector<2> user)
{
	this->angle = angle;
	this->skin.Location = location;
	this->enemy = user;
}