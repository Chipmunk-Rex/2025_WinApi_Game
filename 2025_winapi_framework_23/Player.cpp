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
#include "CardManager.h"
#include "ExplosionEffect.h"
#include "UIManager.h"

Player::Player()
	: middleTexture(nullptr)
	, m_turretTex(nullptr)
	, fireCooldownStat(1.f)
	, projectileScaleStat(1.f)
{
	leftTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Player_Left");
	middleTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Player_Middle");
	rightTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Player_Right");
	m_turretTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player_Turret");
	m_turretMaskTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player_Turret_Mask");

	currentTexture = middleTexture;

	Collider* collider = AddComponent<Collider>();
	collider->SetName(L"Player");
	collider->SetSize({ 50.f,50.f });
	rb = AddComponent<Rigidbody>();
	rb->SetUseGravity(false);
	rb->SetBounciness(0.f);
	rb->SetContiniuouse(true);


	Health* health = AddComponent<Health>();
	health->SetHealth(200);
	health->AddListener([this](double x, double y) { HandleHitEvent(x, y); });
	health->SetDestroyOnDead(false);


	PlayerProjectile* proj = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<PlayerProjectile>(Layer::PROJECTILE);
	AddProjectile(proj);

	GET_SINGLE(PlayerManager)->SetPlayer(this);

	SetPos({ WINDOW_WIDTH / 2 ,  WINDOW_HEIGHT - 45 });
	SetSize({ 100,100 });
};
Player::~Player()
{
	GET_SINGLE(PlayerManager)->SetPlayer(nullptr);
}
void Player::Update()
{
	if (isDead)
		return;
	Vec2 dir = {};
	if (GET_KEY(KEY_TYPE::A))
		dir.x -= 1.f;
	if (GET_KEY(KEY_TYPE::D))
		dir.x += 1.f;
	//if (GET_KEY(KEY_TYPE::W)) dir.y -= 1.f;
	//if (GET_KEY(KEY_TYPE::S)) dir.y += 1.f;


	if (dir.x < 0)
		currentTexture = leftTexture;
	else if (0 < dir.x)
		currentTexture = rightTexture;
	else
		currentTexture = middleTexture;

	rb->SetVelocity(dir.Normalize() * 200.f * moveSpeed);

	if (CanShoot())
	{
		if ((GET_KEYDOWN(KEY_TYPE::LBUTTON) || GET_KEY(KEY_TYPE::LBUTTON))
			&& GET_SINGLE(UIManager)->isHovering() == false)
			ShootProjectile();
	}
	else if (fireTimer < fireCooldownStat.GetValue() && projectiles.size() != 0)
	{
		fireTimer += fDT;
	}

	if (m_offset.y < 0)
		m_offset.y += fDT * 20;
	else
	{
		m_offset.y = 0;
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
	float projectileScale = this->projectileScaleStat.GetValue();
	proj->Scale({ projectileScale, projectileScale });
	Vec2 shootDir = GetShootDir();
	proj->Shoot(shootDir * 500);

	m_offset = Vec2(0, -10);

	fireTimer -= fireCooldownStat.GetValue();
}

Vec2 Player::GetShootDir()
{
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vec2 playerPos = GetPos();
	Vec2 dir = { mousePos.x - playerPos.x, mousePos.y - playerPos.y };
	return dir.Normalize();
}

void Player::HandleHitEvent(double _prev, double _health)
{
	if (_health <= 0.0f)
	{
		isDead = true;
		ExplosionEffect* explosion = GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn<ExplosionEffect>(Layer::EFFECT);
		explosion->SetPos(this->GetPos());
	}
}

void Player::AddProjectile(PlayerProjectile* _proj)
{
	projectiles.push(_proj);
	_proj->SetActive(false);
	_proj->OnPlayerCollect(this);
}


void Player::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	LONG width = currentTexture->GetWidth();
	LONG height = currentTexture->GetHeight();

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x
		, size.y
		, currentTexture->GetTextureDC()
		, 0, 0, width, height, RGB(255, 0, 255));

	ComponentRender(_hdc);

	const float lineDistance = 30;
	const float lineWidth = 30;
	Vec2 shootDir = this->GetShootDir();
	float angle = shootDir.GetAngleRad({ 0,1 });
	Vec2 offset = m_offset.Rotate(angle);
	if (shootDir.x > 0)
		offset.x *= -1;
	Vec2 turretPos = GetPos() + offset;
	Vec2 leftBottom = turretPos + shootDir.Rotate(-90) * lineWidth;
	Vec2 leftTop = turretPos + shootDir * lineDistance + shootDir.Rotate(-90) * lineWidth;
	Vec2 rightTop = turretPos + shootDir * lineDistance + shootDir.Rotate(90) * lineWidth;

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
}

void Player::EnterCollision(Collider* _other)
{
	if (PlayerProjectile* myProjectile = dynamic_cast<PlayerProjectile*>(_other->GetOwner()))
	{
	}
}

void Player::StayCollision(Collider* _other)
{
}

void Player::ExitCollision(Collider* _other)
{
}


void Player::LevelUp()
{
	++level;
	GET_SINGLE(CardManager)->ShowCard(3);
}