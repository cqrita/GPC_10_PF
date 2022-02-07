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

			}			
		}
	}
}

void EntityManager::misCollision()
{
	for (Agent* agent : agents)
	{
		for (Player* player : players)
		{			
			if (agent == player) continue;

			for (Missile* missile : player->missiles)
			{				
				if (agent->body.Collide(missile->body))
				{					
					agent->misCollide();
					missile->duration = 100;
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
