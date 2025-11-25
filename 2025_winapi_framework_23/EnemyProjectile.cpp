#include "pch.h"
#include "EnemyProjectile.h"
#include "Health.h"
#include "Collider.h"
#include "SceneManager.h"

EnemyProjectile::EnemyProjectile(): _damage(0),_timer(0.f),_lifeTime(5.f)
{
	auto* col = GetComponent<Collider>();
	col->SetName(L"EnemyProjectile");
}

EnemyProjectile::~EnemyProjectile()
{

}

void EnemyProjectile::Update()
{
	if (_timer >= 1)
	{
		Projectile::Update();
	}
	else
	{
		Translate({ 0.f, fDT * 20.f, });
	}

	
}

void EnemyProjectile::LateUpdate()
{
	
	if (GetIsDead())return;

	_timer += fDT;
	if (_timer >= _lifeTime)
	{
		GET_SINGLE(SceneManager)->RequestDestroy(this);
	}

	Vec2 pos = GetPos();
	if (pos.x > WINDOW_WIDTH + 100 || pos.x < -100 || pos.y > WINDOW_HEIGHT + 100 || pos.y < -100)
		GET_SINGLE(SceneManager)->RequestDestroy(this);
}

void EnemyProjectile::EnterCollision(Collider* _other)
{
	if (GetIsDead())return;
	if (_other->GetName() == L"Player")
	{
		_other->GetOwner()->GetComponent<Health>()->TakeDamage(5);
		GET_SINGLE(SceneManager)->RequestDestroy(this);
	}
	else if (_other->GetName() == L"PlayerProjectile")
	{

		GET_SINGLE(SceneManager)->RequestDestroy(this);
	}

}

void EnemyProjectile::StayCollision(Collider* _other)
{
}

void EnemyProjectile::ExitCollision(Collider* _other)
{
}
