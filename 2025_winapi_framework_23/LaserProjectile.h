#pragma once
#include "PlayerProjectile.h"
class LaserProjectile : public PlayerProjectile
{

public:
	LaserProjectile();
	~LaserProjectile() override;
public:
	void EnterCollision(Collider* _other) override;
};

