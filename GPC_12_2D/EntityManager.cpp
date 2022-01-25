#include "EntityManager.h"

void EntityManager::Start()
{

}

void EntityManager::Update()
{
	this->entCollision();
}

void EntityManager::End()
{

}

void EntityManager::entCollision()
{
	for (int i = 0; i < players.size(); i++)
	{
		for (int j = 0; j < players.size(); j++)
		{
			if (i == j) continue;
			
			for (Missile* missile: players[j]->missiles)
			{
				if (players[i]->body.Collide(missile->body))
				{

				}
			}			
		}
	}
}
