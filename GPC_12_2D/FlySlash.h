#pragma once
#include "Missile.h"
class FlySlash final : public Missile
{
public:
	void  Start()  override;
	void Update()  override;
	FlySlash(float angle, Vector<2> location, Vector<2> user);
};

