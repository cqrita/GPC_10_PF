#include "Missile.h"
#include "Engine/Time.h"
void Missile::Start()
{
	duration = 0;
}

void Missile::Update()
{
	duration += Engine::Time::Get::Delta();
	if (duration > 100)
	{
		this->End();
	}
}

void Missile::End()
{
	this->~Missile();
}


