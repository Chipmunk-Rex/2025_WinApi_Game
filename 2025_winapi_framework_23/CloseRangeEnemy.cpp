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

void CloseRangeEnemy::HandleChangeHealth(int _health)
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
}