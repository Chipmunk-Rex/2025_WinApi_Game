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
