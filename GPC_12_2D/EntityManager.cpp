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
	for (Agent* agent:agents)
	{
		for (Player* player : players)
		{
			if (agent == player) continue;
			
			for (Missile* missile: player->missiles)
			{
				if (agent->body.Collide(missile->body))
				{

				}
			}			
		}
	}
}
