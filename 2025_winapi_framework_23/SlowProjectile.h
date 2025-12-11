#pragma once
#include"PlayerProjectile.h"
class SlowProjectile : public PlayerProjectile
{
public:
	SlowProjectile();
	~SlowProjectile() override;
public:
	void EnterCollision(Collider* _other) override;
public:
	void OnPlayerCollect(Player* player) override;
private:
	int collisionCount = 0;
};

