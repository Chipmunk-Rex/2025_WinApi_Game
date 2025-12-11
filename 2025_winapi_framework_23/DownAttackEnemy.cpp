#include "pch.h"
#include "DownAttackEnemy.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "DamageText.h"
#include "PlayerManager.h"
#include "SceneManager.h"

DownAttackEnemy::DownAttackEnemy() : _moveDelayTimer(0), _attackMoveStartPos({0,0})
{
	m_isDead = false;
	m_isAttacking = false;

	SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"DownAttackEnemy_1"));
}

void DownAttackEnemy::Update()
{
	if (m_isDead) return;
	if (m_isAttacking)
	{
		_moveDelayTimer += fDT;

		if (_moveDelayTimer >= 1.25f)
		{
			Vec2 pos = GetPos();
			Rigidbody* rbCompo = GetRbCompo();

			if (pos.y >= WINDOW_HEIGHT + 150)
			{
				m_isDead = true;
				GET_SINGLE(SceneManager)->RequestDestroy(this);
			}

			rbCompo->SetVelocity({ 0,500 });

			Player* player = GetTarget();
			if (player == nullptr) return;
			Vec2 playerPos = player->GetPos();

			Vec2 dir = playerPos - pos;
			Vec2 p = playerPos - pos;

			Vec2 offset[2] = { {50,50},{-50,-50} };

			if (p.x <= offset[0].x && p.x >= offset[1].x && p.y <= offset[0].y && p.y >= offset[1].y)
			{
				Health* playerHealth = player->GetComponent<Health>();
				if (playerHealth == nullptr) return;
				if (!GetIsDead())
				{
					playerHealth->TakeDamage(_damage);
					GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(this);
				}
			}
		}
		else
		{
			Vec2 newPos = _attackMoveStartPos + Vec2{ rand() % 10 - 5 ,  rand() % 10 - 5 };
			SetPos(newPos);
		}

		
	}
	else
		CloseRangeEnemy::Update();


}

void DownAttackEnemy::Render(HDC _hdc)
{
	CloseRangeEnemy::Render(_hdc);
}

void DownAttackEnemy::HandleHitEvent(double _prev, double _health)
{
	if (!m_isAttacking) _attackMoveStartPos = GetPos();

	m_isAttacking = true;
	if (_health <= 0)
	{
		GET_SINGLE(PlayerManager)->AddExp(10);
	}

	double maxHealth = GetMaxHealth();

	double normal = _health / maxHealth;

	if (normal <= 0.3f)
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"DownAttackEnemy_3"));
	}
	else if (normal <= 0.7f)
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"DownAttackEnemy_2"));
	}
	else
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"DownAttackEnemy_1"));
	}

	Scene* curScene = GET_SINGLE(SceneManager)->GetCurScene();

	double defaultVal = _prev - _health;

	Vec2 pos = GetPos();
	pos.x += rand() % 20 - 10;
	pos.y += rand() % 10 - 5;
	DamageText* damageText = curScene->Spawn<DamageText>(Layer::DAMAGETEXT, pos, { 50,50 });
	damageText->SetDamage(defaultVal);
}
