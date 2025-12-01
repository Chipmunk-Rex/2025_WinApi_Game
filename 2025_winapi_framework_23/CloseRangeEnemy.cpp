#include "pch.h"
#include "Enemy.h"
#include "Collider.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Health.h"
#include "TimeManager.h"
#include "CloseRangeEnemy.h"
#include "DamageText.h"

CloseRangeEnemy::CloseRangeEnemy()
{
}

CloseRangeEnemy::~CloseRangeEnemy()
{
}

void CloseRangeEnemy::Update()
{
	Enemy::Update();
}

void CloseRangeEnemy::Render(HDC _hdc)
{
	GDISelector pen(_hdc, PenType::GREEN);
	Enemy::Render(_hdc);
}

void CloseRangeEnemy::HandleHitEvent(double _prev, double _health)
{
	double maxHealth = GetMaxHealth();

	double normal = _health / maxHealth;

	if (normal <= 0.3f)
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_3"));
	}
	else if (normal <= 0.7f)
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_2"));
	}

	std::shared_ptr<Scene> curScene = GET_SINGLE(SceneManager)->GetCurScene();

	double defaultVal = _prev - _health;

	Vec2 pos = GetPos();
	pos.x += rand() % 60 - 30;
	pos.y += rand() % 30 - 15;
	DamageText* damageText = curScene->Spawn<DamageText>(Layer::DAMAGETEXT, pos, { 50,50 });
	damageText->SetDamage(defaultVal);
}