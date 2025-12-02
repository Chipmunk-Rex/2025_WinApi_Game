#include "pch.h"
#include "Enemy.h"
#include "Collider.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Health.h"
#include "TimeManager.h"
#include "Animator.h"
Enemy::Enemy() : m_pTex(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_1");

	if (m_pTex == nullptr)
		cout << endl << "ming" << endl;
	/*auto* anim = AddComponent<Animator>();
	anim->CreateAnimation(L"JiwooFront", m_pTex, { 0.f, 150.f }, { 50.f,50.f }, { 50.f,0.f }, 5, 0.1f);
	anim->Play(L"JiwooFront");*/

	auto* col = AddComponent<Collider>();
	m_rbCompo = AddComponent<Rigidbody>();
	m_healthCompo = AddComponent<Health>();

	std::function<void(double, double)> delegate =
		[this](double x, double y) { HandleHitEvent(x,y); };

	m_healthCompo->SetHealth(100);
	m_healthCompo->AddListener(delegate);
	m_rbCompo->SetMass(1.f);
	m_rbCompo->SetUseGravity(false);
	m_rbCompo->SetVelocity({0,-20});
	col->SetSize({ 50,50 });
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	m_rbCompo->SetVelocity({ 0,20 });
}

void Enemy::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	/*ELLIPSE_RENDER(_hdc, pos.x, pos.y
		, size.x, size.y);*/
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

void Enemy::EnterCollision(Collider* _other)
{
	// 총알?
	// 트리거 ?
	if (_other->GetName() == L"PlayerBullet")
	{
		GetComponent<Health>()->TakeDamage(5);
		//GET_SINGLE(SceneManager)->RequestDestroy(_other->GetOwner());
	}

	// 물리충돌 

}

void Enemy::StayCollision(Collider* _other)
{
}

void Enemy::ExitCollision(Collider* _other)
{
}








