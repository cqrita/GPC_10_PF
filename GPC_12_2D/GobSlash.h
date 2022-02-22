#pragma once
#include "Missile.h"
class GobSlash final : public Missile
{
public:
	void  Start()  override;
	void Update()  override;
	GobSlash(float angle, Vector<2> location, Vector<2> user);
};
