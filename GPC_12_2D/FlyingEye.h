#pragma once
#include "Enemy.h"
class FlyingEye : public Enemy
{
public:
	void  Start()  override;
	void Update()  override;
	void End() override;
	void createMissile(float x, float y);
};