#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "Projectile.h"	
#include "SceneManager.h"
#include "Scene.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Rigidbody.h"
Player::Player()
	: m_pTex(nullptr)
{
	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\planem.bmp";
	//m_pTex->Load(path); 
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Jiwoo");
	AddComponent<Collider>();
	auto* anim = AddComponent<Animator>();
	anim->CreateAnimation(L"JiwooFront", m_pTex, { 0.f, 150.f }, { 50.f,50.f }, { 50.f,0.f }, 5, 0.1f);
	anim->Play(L"JiwooFront");
	rb = AddComponent<Rigidbody>();
	rb->SetUseGravity(false);
}
Player::~Player()
{
	//SAFE_DELETE(m_pTex);
}
void Player::Update()
{
	// transform.translate 
	// rigidbody
	//
	//Vec2 pos = GetPos();
	//if (GET_KEY(KEY_TYPE::A))
	//	pos.x -= 300.f * fDT;
	//if (GET_KEY(KEY_TYPE::D))
	//	pos.x += 300.f * fDT;
	//if (GET_KEY(KEY_TYPE::W))
	//	pos.y -= 300.f * fDT;
	//if (GET_KEY(KEY_TYPE::S))
	//	pos.y += 300.f * fDT;
	//SetPos(pos);

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
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
		CreateProjectile();

}

void Player::CreateProjectile()
{
	Projectile* proj = new Projectile;
	Vec2 pos = GetPos();
	//pos.y -= GetSize().y / 2.f;
	proj->SetPos(pos);
	proj->SetSize({ 20.f,20.f });
	//proj->SetAngle(angle * PI / 180);
	proj->SetDir(GetShootDir() * 500);
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(proj, Layer::PROJECTILE);
}

Vec2 Player::GetShootDir()
{
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vec2 playerPos = GetPos();
	Vec2 dir = { mousePos.x - playerPos.x, mousePos.y - playerPos.y };
	dir.Normalize();
	return dir;
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
	//::TransparentBlt(_hdc
	//	, (int)(pos.x - size.x / 2)
	//	, (int)(pos.y - size.y / 2)
	//	, size.x
	//	, size.y
	//	, m_pTex->GetTextureDC()
	//	, 0, 0, width,height, RGB(255,0,255));

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

	const float lineDistance = 100;
	const float lineWidth= 10;
	Vec2 shootDir = this->GetShootDir();

	Vec2 leftBottom = GetPos() + shootDir.Rotate(-90) * lineWidth;
	Vec2 rightBottom = GetPos() + shootDir.Rotate(90) * lineWidth;
	Vec2 leftTop = GetPos() + shootDir * lineDistance + shootDir.Rotate(-90) * lineWidth;
	Vec2 rightTop = GetPos() + shootDir * lineDistance + shootDir.Rotate(90) * lineWidth;

	POINT arr[4] =
	{
		(POINT)leftBottom,
		(POINT)rightBottom,
		(POINT)rightTop,
		(POINT)leftTop
	};
	Polygon(_hdc, arr, 4);
}

void Player::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Floor")
	{
		Rigidbody* rb = GetComponent<Rigidbody>();
		rb->SetGrounded(true);
	}
	cout << "hi";
}

void Player::StayCollision(Collider* _other)
{
}

void Player::ExitCollision(Collider* _other)
{
}


