#include "pch.h"
#include "LaserProjectile.h"
#include "CollisionManager.h"
#include "Health.h"
#include "ResourceManager.h"

LaserProjectile::LaserProjectile()
{
	SetTexture(GET_SINGLE(ResourceManager)->GetTexture(L"Ball2"));
}

LaserProjectile::~LaserProjectile()
{
}

void LaserProjectile::EnterCollision(Collider* _other)
{
	vector<Collider*> outColliders;
	GET_SINGLE(CollisionManager)->OverlapBox(_other->GetWorldPos(), { 1000, 0 }, LayerToMask(Layer::ENEMY), outColliders);
	for (Collider* collider : outColliders)
	{
		Health* health = collider->GetOwner()->GetComponent<Health>();
		if (health != nullptr && !health->GetIsDead())
		{
			health->TakeDamage(10.0);
		}
	}
}
