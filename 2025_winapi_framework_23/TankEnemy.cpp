#include "pch.h"
#include "TankEnemy.h"
#include "Collider.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "PlayerManager.h"
#include "DamageText.h"
#include "SceneManager.h"

TankEnemy::TankEnemy()
{
	SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"TankEnemyTile"));
	auto* col = GetComponent<Collider>();
	col->SetSize({ 100,50 });
}
void TankEnemy::Update()
{
	CloseRangeEnemy::Update();
}
void TankEnemy::Render(HDC _hdc)
{
	CloseRangeEnemy::Render(_hdc);
}

void TankEnemy::HandleHitEvent(double _prev, double _health)
{
	if (_health <= 0)
	{
		GET_SINGLE(PlayerManager)->AddExp(5);
	}

	GET_SINGLE(ResourceManager)->Play(L"TankHitSound");

	double maxHealth = GetMaxHealth();

	double normal = _health / maxHealth;

	if (normal <= 0.3f)
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"TankEnemyTile_3"));
	}
	else if (normal <= 0.7f)
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"TankEnemyTile_2"));
	}
	else
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"TankEnemyTile"));
	}

	Scene* curScene = GET_SINGLE(SceneManager)->GetCurScene();

	double defaultVal = _prev - _health;

	Vec2 pos = GetPos();
	pos.x += rand() % 20 - 10;
	pos.y += rand() % 10 - 5;
	DamageText* damageText = curScene->Spawn<DamageText>(Layer::DAMAGETEXT, pos, { 50,50 });
	damageText->SetDamage(defaultVal);

	//_isHit = true;
}
