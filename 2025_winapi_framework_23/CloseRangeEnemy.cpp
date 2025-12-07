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
#include "Player.h"

CloseRangeEnemy::CloseRangeEnemy() :
	_isHit(false),
	_hitDelay(0.1f),
	_hitTimer(0),
	_isAttack(false)
{
}

CloseRangeEnemy::~CloseRangeEnemy()
{
}

void CloseRangeEnemy::Update()
{
	Vec2 pos = GetPos();



	if (pos.y >= WINDOW_HEIGHT)
	{
		_isAttack = true;
		
	}

	if (_isAttack)
	{
		Player* player = GetTarget();
		if (player == nullptr) return;
		Vec2 playerPos = player->GetPos();
		Rigidbody* rbCompo = GetRbCompo();

		Vec2 dir = playerPos - pos;
		Vec2 p = playerPos - pos;
		dir = dir.Normalize();
		rbCompo->AddForce(dir * 1000.f);

		Vec2 offset[2] = { {50,50},{-50,-50} };

		if (p.x <= offset[0].x && p.x >= offset[1].x && p.y <= offset[0].y && p.y >= offset[1].y)
		{
			Health* playerHealth = player->GetComponent<Health>();
			if (playerHealth == nullptr) return;
			playerHealth->TakeDamage(_damage);
			GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(this);
		}
	}
	else
	{
		Enemy::Update();

		if (_isHit)
		{
			_hitTimer += fDT;
			if (_hitDelay <= _hitTimer)
			{

				double normal = GetCurHealth() / GetMaxHealth();

				if (normal <= 0.3f)
				{
					SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_3"));
				}
				else if (normal <= 0.7f)
				{
					SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_2"));
				}
				else
				{
					SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_1"));
				}

				_hitTimer = 0;
				_isHit = false;
			}
		}
	}
	
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
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_3_Hit"));
	}
	else if (normal <= 0.7f)
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_2_Hit"));
	}
	else
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_2_Hit"));
	}

	std::shared_ptr<Scene> curScene = GET_SINGLE(SceneManager)->GetCurScene();

	double defaultVal = _prev - _health;

	Vec2 pos = GetPos();
	pos.x += rand() % 20 - 10;
	pos.y += rand() % 10 - 5;
	DamageText* damageText = curScene->Spawn<DamageText>(Layer::DAMAGETEXT, pos, { 50,50 });
	damageText->SetDamage(defaultVal);

	_isHit = true;
}