#include "pch.h"
#include "Enemy.h"
#include "Collider.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Health.h"
#include "TimeManager.h"
Enemy::Enemy()
{
	AddComponent<Collider>();
	Rigidbody* rb = AddComponent<Rigidbody>();
	Health* health = AddComponent<Health>();
	rb->SetMass(1.f);
	rb->SetUseGravity(false);
	health->SetHealth(10);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Translate({ 0.f, fDT * 100.f, });
}

void Enemy::Render(HDC _hdc)
{
	//HBRUSH hbrush = ::CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	//HBRUSH holdbrush = (HBRUSH)::SelectObject(_hdc, hbrush);
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	RECT_RENDER(_hdc, pos.x, pos.y
		, size.x, size.y);
	//::SelectObject(_hdc, holdbrush);
	//::DeleteObject(hbrush);
	ComponentRender(_hdc);

}

void Enemy::EnterCollision(Collider* _other)
{
	cout << "EnterCollision" << endl;
	// 총알?
	// 트리거 ?
	if (_other->GetName() == L"PlayerBullet")
	{
		// 삭제
		//GET_SINGLE(SceneManager)->RequestDestroy(this);
		//GET_SINGLE(SceneManager)->RequestDestroy(_other->GetOwner());
	}

	// 물리충돌 

}

void Enemy::StayCollision(Collider* _other)
{
	cout << "StayCollision" << endl;
}

void Enemy::ExitCollision(Collider* _other)
{
	cout << "ExitCollision" << endl;
}








