#include "pch.h"
#include "PlayerProjectile.h"
#include "Player.h"
#include "Collider.h"

PlayerProjectile::PlayerProjectile() 
	: Projectile(), _damage(0)
{
}

PlayerProjectile::~PlayerProjectile()
{
}

void PlayerProjectile::Update()
{
	shootTimer += fDT;
}

void PlayerProjectile::Render(HDC _hdc)
{
	if(IsActive())
		Projectile::Render(_hdc);
}

void PlayerProjectile::EnterCollision(Collider* _other)
{
	//if (typeid(*_other->GetOwner()) == typeid(Player))
	//{
	//}
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
	shootTimer = 0;
	cout << "PlayerProjectile Shoot!" << endl;
}
////////////