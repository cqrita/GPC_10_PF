#pragma once
#include "Enemy.h"
class Mushroom : public Enemy
{
public:
	void  Start()  override;
	void Update()  override;
	void createMissile(float x, float y);
};