#include "pch.h"
#include "LaserProjectile.h"
#include "CollisionManager.h"
#include "Health.h"
#include "ResourceManager.h"

LaserProjectile::LaserProjectile() : PlayerProjectile()
{
	SetTexture(GET_SINGLE(ResourceManager)->GetTexture(L"Projectile_Saturn"));
	SetSize({ 80.f, 80.f });
}

LaserProjectile::~LaserProjectile()
{
}

void LaserProjectile::EnterCollision(Collider* _other)
{
	cout << GetSize().x << ' ' << GetSize().y << endl;
	PlayerProjectile::EnterCollision(_other);
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

void LaserProjectile::Shoot(Vec2 _dir)
{
	PlayerProjectile::Shoot(_dir);
	this->GetCollider()->SetSize(GetSize() * 0.4);
}
