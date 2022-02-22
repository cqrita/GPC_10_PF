#include "MushMissile.h"
#include "Engine/Time.h"
void MushMissile::Start()
{
	{
		skin.Name = "Animation/Black/Bulleta";


		skin.Length = Vector<2>(10, 10);

	}
	{
		body.Radius = skin.Length[0] / 2;
		body.Center = Point(skin.Location[0], skin.Location[1]);

		box.Name = "Image/GBB";
		box.Length = skin.Length;

	}
	{
		damage = 1;
	}

	{
		speed = 1000;
	}
	{
		EnemyHoming = false;
	}
	duration = 0;
}

void MushMissile::Update()
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
	}
}

MushMissile::MushMissile(float angle, Vector<2> location, Vector<2> user)
{
	this->angle = angle;
	this->skin.Location = location;
	this->enemy = user;
}
