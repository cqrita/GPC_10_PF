#pragma once
#include "Missile.h"
class Melee final : public Missile
{
public:
	void  Start()  override;
	void Update()  override;
	Melee(float angle, Vector<2> location , Vector<2> user);
};