#pragma once
#include "Engine/Vector.h"
#include "Enemy.h"
class LevelManager
{
	void setLevel(int i);
	void setCam(Vector<2> location);
	Enemy getEnemies();
};