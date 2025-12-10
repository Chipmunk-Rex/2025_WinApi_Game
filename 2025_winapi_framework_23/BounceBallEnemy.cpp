#include "pch.h"
#include "BounceBallEnemy.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "PlayerManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "DamageText.h"

BounceBallEnemy::BounceBallEnemy() :
	_timer(0),
	_attackDelay(7),
	_attackTime(2),
	_damage(1),
	_projectile(nullptr),
	_isHit(false),
	_hitDelay(0.1f),
	_hitTimer(0),
	_isAttack(false),
	_isAttacking(false),
	_moveDelayTimer(0),
	_attackMoveStartPos({0,0})
{

	SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"BounceBallEnemy"));
	_attackDelay = rand() % 20 + 17;

}

void BounceBallEnemy::Aattack()
{
	double normal = GetCurHealth() / GetMaxHealth();

	if (normal <= 0.3f)
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"MainTile_3"));
	}
	else if (normal <= 0.7f)
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"MainTile_2"));
	}
	else
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"MainTile"));
	}

	Object* player = GetTarget();
	if (player == nullptr) return;

	auto curScene = GET_SINGLE(SceneManager)->GetCurScene();
	BounceEnemyProjectile* proj = new BounceEnemyProjectile;
	Vec2 pos = GetPos();
	Vec2 shootDir = this->GetShootDir();
	float angle = shootDir.GetAngleRad({ 0,1 });
	Vec2 newPos = pos.Rotate(angle);
	Vec2 playerPos = player->GetPos();
	proj->SetPos(pos);
	proj->SetSize({ 25.f,25.f });
	proj->Shoot(shootDir * 350);
	proj->SetDamage(_damage);
	curScene->AddObject(proj, Layer::BOUNCEPROJECTILE);
	_projectile = proj;
}

BounceBallEnemy::~BounceBallEnemy()
{
}

void BounceBallEnemy::Update()
{
	Vec2 pos = GetPos();

	if (!_isAttack && pos.y >= WINDOW_HEIGHT - 150)
	{
		_attackMoveStartPos = GetPos();
		_isAttack = true;
		GetRbCompo()->SetVelocity({0,0});
	}

	if (_isAttack)
	{
		_moveDelayTimer += fDT;

		if (_moveDelayTimer >= 1.25f)
		{
			Player* player = GetTarget();
			if (player == nullptr) return;
			Vec2 playerPos = player->GetPos();
			Rigidbody* rbCompo = GetRbCompo();

			Vec2 dir = playerPos - pos;
			Vec2 p = playerPos - pos;
			dir = dir.Normalize();
			rbCompo->SetVelocity(dir * 1000.f);

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
	{
		_timer += fDT;

		if (_isHit)
		{
			_hitTimer += fDT;
			if (_hitDelay <= _hitTimer)
			{

				double normal = GetCurHealth() / GetMaxHealth();

				if (_isAttacking)
				{
					if (normal <= 0.3f)
					{
						SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"MainTile_3"));
					}
					else if (normal <= 0.7f)
					{
						SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"MainTile_2"));
					}
					else
					{
						SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"MainTile"));
					}
				}
				else
				{
					if (normal <= 0.3f)
					{
						SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"BounceBallEnemy_3"));
					}
					else if (normal <= 0.7f)
					{
						SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"BounceBallEnemy_2"));
					}
					else
					{
						SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"BounceBallEnemy"));
					}
				}



				_hitTimer = 0;
				_isHit = false;
			}
		}

		if (!_isAttacking && _timer >= _attackDelay)
		{
			_isAttacking = true;
			Aattack();
		}
	}
}

Vec2 BounceBallEnemy::GetShootDir()
{
	Vec2 targetPos = GetTarget()->GetPos();
	Vec2 thisPos = GetPos();
	Vec2 dir = { targetPos.x - thisPos.x, targetPos.y - thisPos.y };
	return dir.Normalize();
}


void BounceBallEnemy::Render(HDC _hdc)
{
	Enemy::Render(_hdc);
}

void BounceBallEnemy::HandleHitEvent(double _prev, double _health)
{
	if (_health <= 0)
	{
		GET_SINGLE(PlayerManager)->AddExp(7);
	}


	double maxHealth = GetMaxHealth();

	double normal = _health / maxHealth;

	Scene* curScene = GET_SINGLE(SceneManager)->GetCurScene();

	double defaultVal = _prev - _health;

	Vec2 pos = GetPos();
	pos.x += rand() % 20 - 10;
	pos.y += rand() % 10 - 5;
	DamageText* damageText = curScene->Spawn<DamageText>(Layer::DAMAGETEXT, pos, { 50,50 });
	damageText->SetDamage(defaultVal);

	_isHit = true;
}
