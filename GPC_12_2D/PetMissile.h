#pragma once
#include "Missile.h"
class PetMissile final : public Missile
{
public:
	void  Start()  override;
	void Update()  override;
	PetMissile(float angle, Vector<2> location, Vector<2> user);
};