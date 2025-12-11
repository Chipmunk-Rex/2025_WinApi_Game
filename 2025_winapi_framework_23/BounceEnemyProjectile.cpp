#include "pch.h"
#include "BounceEnemyProjectile.h"
#include "Health.h"
#include "Collider.h"
#include "SceneManager.h"
#include "ResourceManager.h"

BounceEnemyProjectile::BounceEnemyProjectile()
{
	SetTexture(GET_SINGLE(ResourceManager)->GetTexture(L"enemyBall"));
	auto* col = GetComponent<Collider>();
	col->SetName(L"EnemyBounceBall");
	col->SetSize({25.f,25.f });
	m_count = 0;
	_damage = 3;
}



BounceEnemyProjectile::~BounceEnemyProjectile()
{
}

void BounceEnemyProjectile::Update()
{
	Projectile::Update();
}

void BounceEnemyProjectile::Render(HDC _hdc)
{
	Projectile::Render(_hdc);
}

void BounceEnemyProjectile::LateUpdate()
{
}

void BounceEnemyProjectile::EnterCollision(Collider* _other)
{
	if (GetIsDead())return;
	++m_count;
	if (_other->GetName() == L"Player")
	{
		_other->GetOwner()->GetComponent<Health>()->TakeDamage(_damage);
	}

	if (m_count >= 10)
		GET_SINGLE(SceneManager)->RequestDestroy(this);
}

