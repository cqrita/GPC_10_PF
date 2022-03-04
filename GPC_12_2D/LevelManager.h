#pragma once
#include "Engine/Vector.h"
#include "Enemy.h"
#include "Item.h"
class LevelManager
{
public:
	void setLevel(int i);
	void setCam(Vector<2> location);
	void setEnemSize(size_t i);
	void setItemSize(size_t i);
	Enemy* getEnemies();
	Item* getItems();
	Vector<2> cam;
	int level;
	size_t enemSize;
	size_t itemSize;
};