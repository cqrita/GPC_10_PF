#pragma once
#include "Missile.h"
class MissileA final : public Missile
{
public:
	void  Start()  override;
	void Update()  override;
	MissileA(float angle, Vector<2> location, Vector<2> user);
};