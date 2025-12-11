#include "pch.h"
#include "SlowProjectile.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Health.h"
#include "Collider.h"
#include "Enemy.h"
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
	if (dynamic_cast<Enemy*>(_other->GetOwner()) != nullptr)
	{
		collisionCount++;
		if (collisionCount > 3)
			collisionCount = 3;
	}
}

void SlowProjectile::OnPlayerCollect(Player* player)
{
	PlayerProjectile::OnPlayerCollect(player);
	Health* health = player->GetComponent<Health>();
	int current = health->GetCurrentHealth();
	int maxHealth = (int)health->GetMaxHealth();
	int targetHealth = current + collisionCount;
	if (targetHealth > maxHealth)
		targetHealth = maxHealth;
	health->SetCurrentHealth(targetHealth);
	collisionCount = 0;
}
