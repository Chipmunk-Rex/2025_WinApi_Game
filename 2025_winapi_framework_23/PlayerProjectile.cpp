#include "pch.h"
#include "PlayerProjectile.h"
#include "Player.h"
#include "Collider.h"

PlayerProjectile::PlayerProjectile() 
	: Projectile(), _damage(0)
{
	SetDefaultSize({ 30.f, 30.f });
}

PlayerProjectile::~PlayerProjectile()
{
}

void PlayerProjectile::Update()
{
}

void PlayerProjectile::Render(HDC _hdc)
{
	if(IsActive())
		Projectile::Render(_hdc);
}

void PlayerProjectile::EnterCollision(Collider* _other)
{
	canCollect = true;
}

void PlayerProjectile::StayCollision(Collider* _other)
{
}

void PlayerProjectile::ExitCollision(Collider* _other)
{
}

void PlayerProjectile::Shoot(Vec2 _dir)
{
	Projectile::Shoot(_dir);
	SetActive(true);
	this->GetCollider()->SetSize(GetSize());
	canCollect = false;
}