#include "pch.h"
#include "LaserProjectile.h"
#include "CollisionManager.h"
#include "Health.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RingEffect.h"

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
	PlayerProjectile::EnterCollision(_other);

	//Vec2 targetPos = _other->GetWorldPos();
	Vec2 targetPos = this->GetPos();

	vector<Collider*> outColliders;
	GET_SINGLE(CollisionManager)->OverlapBox(targetPos, { 150, 150 }, LayerToMask(Layer::ENEMY), outColliders);
	for (Collider* collider : outColliders)
	{
		Health* health = collider->GetOwner()->GetComponent<Health>();
		if (health != nullptr && !health->GetIsDead())
		{
			health->TakeDamage(10.0);
		}
	}
	RingEffect* ring = GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn<RingEffect>(Layer::PROJECTILE);
	ring->SetPos(targetPos);
	ring->SetStartRadius(20.f);
	ring->SetMaxRadius(180.f);
	ring->SetDuration(0.35f);
}

void LaserProjectile::Shoot(Vec2 _dir)
{
	PlayerProjectile::Shoot(_dir);
	this->GetCollider()->SetSize(GetSize() * 0.4);
}
