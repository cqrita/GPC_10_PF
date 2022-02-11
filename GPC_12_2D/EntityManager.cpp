#include "EntityManager.h"
#include <iostream>
void EntityManager::Start()
{

}

void EntityManager::Update()
{	
	this->entCollision();
	this->misCollision();
	this->checkState();
}

void EntityManager::End()
{

}

void EntityManager::entCollision()
{
	for (Agent* agent : agents)
	{
		for (Player* player : players)
		{
			if (agent == player) continue;			
			if (agent->body.Collide(player->body))
			{
				player->entCollide(agent);
				agent->entCollide(player);
			}			
		}
	}
}

void EntityManager::misCollision()
{
	
	for (Player* player : players)
	{						
		for (Missile* missile : player->missiles)
		{
			for (Agent* agent : agents)
			{
				if (agent == player) continue;
								
				if (agent->body.Collide(missile->body))
				{
					agent->misCollide(missile);
					missile->duration = 100;
				}
				if (agent->state == 1)
				{
					missile->getEnemy(Vector<2>(agent->body.Center.x, agent->body.Center.y));
				}

			}
		}
	}
	
}

void EntityManager::addAgent(Agent* agent)
{
	agents.push_back(agent);
}


void EntityManager::addPlayer(Player* player)
{
	players.push_back(player);
	this->addAgent(player);
}

void EntityManager::addEnemy(Enemy* enemy)
{
	enemies.push_back(enemy);
	this->addAgent(enemy);
}

void EntityManager::checkState()
{
	for (auto a = agents.begin(); a != agents.end() && !agents.empty();)
	{
		if ((*a)->state==1)
		{
			++a;
		}
		else
		{
			a = agents.erase(a);
		}
	}
	
}
