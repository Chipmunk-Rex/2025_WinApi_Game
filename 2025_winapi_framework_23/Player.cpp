#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "Projectile.h"	
#include "SceneManager.h"
#include "Scene.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Rigidbody.h"
#include "Health.h"
#include "PlayerProjectile.h"
#include "LaserProjectile.h"
#include "PlayerManager.h"

Player::Player()
	: m_pTex(nullptr)
	, m_turretTex(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player_Middle");
	m_turretTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player_Turret");
	m_turretMaskTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player_Turret_Mask");

	Collider* collider = AddComponent<Collider>();
	collider->SetName(L"Player");
	collider->SetSize({ 50.f,50.f });
	//auto* anim = AddComponent<Animator>();
	//anim->CreateAnimation(L"JiwooFront", m_pTex, { 0.f, 150.f }, { 50.f,50.f }, { 50.f,0.f }, 5, 0.1f);
	//anim->Play(L"JiwooFront");
	rb = AddComponent<Rigidbody>();
	rb->SetUseGravity(false);
	rb->SetBounciness(0.f);
	rb->SetContiniuouse(true);


	Health* health = AddComponent<Health>();
	health->SetHealth(100);

	fireCooldown = 0.2f;


	PlayerProjectile* proj = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<PlayerProjectile>(Layer::PROJECTILE, { 0,0 }, { 50,50 });
	AddProjectile(proj);
	cout << "Player Created\n";
	cout << projectiles.size() << "\n";
	cout << CanShoot() << "\n";

	GET_SINGLE(PlayerManager)->SetPlayer(this);
}
Player::~Player()
{
	//SAFE_DELETE(m_pTex);
	GET_SINGLE(PlayerManager)->SetPlayer(nullptr);
}
void Player::Update()
{

	//cout << CanShoot() << "\n";
	Vec2 dir = {};
	if (GET_KEY(KEY_TYPE::A)) dir.x -= 1.f;
	if (GET_KEY(KEY_TYPE::D)) dir.x += 1.f;
	if (GET_KEY(KEY_TYPE::W)) dir.y -= 1.f;
	if (GET_KEY(KEY_TYPE::S)) dir.y += 1.f;

	//Translate({ dir.x * 300.f * fDT, dir.y * 300.f * fDT });
	rb->SetVelocity(dir.Normalize() * 300.f);
	// 크기변경
	float scaleDelta = 0.f;
	float scaleSpeed = 1.f;
	if (GET_KEY(KEY_TYPE::Q))
		scaleDelta += scaleSpeed * fDT;
	if (GET_KEY(KEY_TYPE::E))
		scaleDelta -= scaleSpeed * fDT;

	float factor = 1.f + scaleDelta;
	Scale({ factor, factor });
	if (CanShoot())
	{
		if (GET_KEYDOWN(KEY_TYPE::LBUTTON) || GET_KEY(KEY_TYPE::LBUTTON))
			ShootProjectile();
	}
	else if (fireTimer < fireCooldown)
	{
		fireTimer += fDT;
	}
}

void Player::FixedUpdate(float _fixedDT)
{
	std::vector<Collider*> outColliders;
	GET_SINGLE(CollisionManager)->OverlapBox(GetPos(), GetSize(), LayerToMask(Layer::PROJECTILE), outColliders);
	for (auto col : outColliders)
	{
		if (PlayerProjectile* proj = dynamic_cast<PlayerProjectile*>(col->GetOwner()))
			if (proj->CanCollect())
				this->AddProjectile(proj);
	}
}

void Player::ShootProjectile()
{
	Projectile* proj = projectiles.front();
	projectiles.pop();
	Vec2 pos = GetPos();
	proj->SetPos(pos);
	proj->SetSize({ 20.f,20.f });
	proj->Shoot(GetShootDir() * 500);

	fireTimer -= fireCooldown;
}

Vec2 Player::GetShootDir()
{
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vec2 playerPos = GetPos();
	Vec2 dir = { mousePos.x - playerPos.x, mousePos.y - playerPos.y };
	return dir.Normalize();
}

void Player::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	//RECT_RENDER(_hdc, pos.x, pos.y
	 //                , size.x, size.y);
	///m_pTex->getwidth();

	LONG width = m_pTex->GetWidth();
	LONG height = m_pTex->GetHeight();

	//// blt 종류
	// bitblt >>>>>> stretch >>> transparenblt
	// 
	//// 1. bitblt - 1:1 매칭, 고속 복사
	//::BitBlt(_hdc
	//	,(int)(pos.x - size.x / 2)
	//	, (int)(pos.y - size.y / 2)
	//	, width
	//	, height
	//	,m_pTex->GetTextureDC()
	//	,0,0, SRCCOPY);

	//// 2. transparentblt - 색깔 뺄때
	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x
		, size.y
		, m_pTex->GetTextureDC()
		, 0, 0, width, height, RGB(255, 255, 255));

	ComponentRender(_hdc);

	//// 3. Stretcthblt - 확대, 축소
	//::StretchBlt(_hdc
	//	, (int)(pos.x - size.x / 2)
	//	, (int)(pos.y - size.y / 2)
	//	, size.x
	//	, size.y
	//	, m_pTex->GetTextureDC()
	//	, 0, 0, width, height,SRCCOPY);

	// 4. - 알파값 조절
	//::AlphaBlend()

	// 5.  - 회전
	//::PlgBlt();

	const float lineDistance = 50;
	const float lineWidth = 50;
	Vec2 shootDir = this->GetShootDir();
	Vec2 leftBottom = GetPos() + shootDir.Rotate(-90) * lineWidth;
	//Vec2 rightBottom = GetPos() + shootDir.Rotate(90) * lineWidth;
	Vec2 leftTop = GetPos() + shootDir * lineDistance + shootDir.Rotate(-90) * lineWidth;
	Vec2 rightTop = GetPos() + shootDir * lineDistance + shootDir.Rotate(90) * lineWidth;

	POINT plg[3] =
	{
		(POINT)leftTop,
		(POINT)rightTop,
		(POINT)leftBottom
	};
	int lineTexW = (int)m_turretTex->GetWidth();
	int lineTexH = (int)m_turretTex->GetHeight();
	::PlgBlt(
		_hdc,
		plg,
		m_turretTex->GetTextureDC(),
		0, 0,
		lineTexW, lineTexH,
		m_turretMaskTex->GetHBitmap(),
		0, 0);
	//else
	//{
	//	POINT arr[4] =
	//	{
	//		(POINT)leftBottom,
	//		(POINT)rightBottom,
	//		(POINT)rightTop,
	//		(POINT)leftTop
	//	};
	//	Polygon(_hdc, arr, 4);
	//}

	//LaycastHit hit;
	//GET_SINGLE(CollisionManager)->BoxCast(GetPos(), GetSize(), GetShootDir(), 10000, Layer::DEFAULT | Layer::PROJECTILE, hit);

	//RECT_RENDER(_hdc, hit.point.x, hit.point.y, GetSize().x, GetSize().y);
}

void Player::EnterCollision(Collider* _other)
{

	if (PlayerProjectile* myProjectile = dynamic_cast<PlayerProjectile*>(_other->GetOwner()))
	{
		//myProjectile->SetActive(false);
	}
}

void Player::StayCollision(Collider* _other)
{
}

void Player::ExitCollision(Collider* _other)
{
}


////////////////////////////////////////////////////////////////////////////////////