#include "EntityManager.h"
#include "Engine/Physics.h"
#include <iostream>
void EntityManager::Start()
{

}

void EntityManager::Update()
{	
	this->entCollision();
	this->misCollision();
	this->eneMisCollision();
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
	for (Agent* agent : agents)
	{
		for (Player* player : players)
		{						
			for (Missile* missile : player->missiles)
			{
				if (agent == player) continue;
								
				if (agent->body.Collide(missile->body))
				{
					agent->misCollide(missile);
					missile->duration = 1000;
				}				
			}
			for (Pet* pet : player->pets)
			{
				if (agent == player) continue;
				pet->getEnemy(Vector<2>(agent->body.Center.x, agent->body.Center.y));
				for (Missile* missile : pet->missiles)
				{					
					if (agent->body.Collide(missile->body))
					{
						agent->misCollide(missile);
						missile->duration = 1000;
					}
					if (agent->state == 1)
					{
						missile->getEnemy(Vector<2>(agent->body.Center.x, agent->body.Center.y));
					}
				}
			}
		}
	}	
}

void EntityManager::eneMisCollision()
{
	for (Enemy* enemy : enemies)
	{
		for (Missile* missile : enemy->missiles)
		{
			for (Player* player : players)
			{				
				if (player->body.Collide(missile->body))
				{
					player->misCollide(missile);
					missile->duration = 1000;
				}
			}
		}
	}
}

MeleeMouse EntityManager::mouseCollision(float x, float y)
{
	for (Enemy* enemy : enemies)
	{
		if (enemy->state == 1)
		{
			Engine::Physics::Component<Point> point = Point(x, y);
			if (enemy->body.Collide(point))
			{
				MeleeMouse melee{ true,enemy->skin.Location };
				return melee;
			}
		}		
	}
	MeleeMouse melee{ false,Vector<2>()};
	return melee;
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
