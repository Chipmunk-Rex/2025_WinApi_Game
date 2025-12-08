#include "pch.h"
#include "Projectile.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Rigidbody.h"
Projectile::Projectile()
{
	SetTexture(GET_SINGLE(ResourceManager)->GetTexture(L"Projectile_Moon"));
	collider = AddComponent<Collider>();
	collider->SetSize({ 20.f,20.f });
	collider->SetName(L"PlayerBullet");
	collider->SetTrigger(true);

	rigidbody = AddComponent<Rigidbody>();
	rigidbody->SetContiniuouse(true);
	rigidbody->SetBounciness(1.f);
}

Projectile::~Projectile()
{
}

void Projectile::Update()
{
}

void Projectile::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	LONG width = m_pTex->GetWidth();
	LONG height = m_pTex->GetHeight();

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x
		, size.y
		, m_pTex->GetTextureDC()
		, 0, 0, width, height, RGB(255, 0, 255));

	ComponentRender(_hdc);
}

void Projectile::EnterCollision(Collider* _other)
{
}

void Projectile::StayCollision(Collider* _other)
{
}

void Projectile::ExitCollision(Collider* _other)
{
}
