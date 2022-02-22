#pragma once
#include "Missile.h"
class MushMissile final : public Missile
{
public:
	void  Start()  override;
	void Update()  override;
	MushMissile(float angle, Vector<2> location, Vector<2> user);
};