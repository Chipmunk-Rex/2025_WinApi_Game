#include "pch.h"
#include "SlowProjectile.h"
#include "ResourceManager.h"
SlowProjectile::SlowProjectile()
{
	SetTexture(GET_SINGLE(ResourceManager)->GetTexture(L"Projectile_Earth"));
}

SlowProjectile::~SlowProjectile()
{
}

void SlowProjectile::EnterCollision(Collider* _other)
{
	PlayerProjectile::EnterCollision(_other);

}
