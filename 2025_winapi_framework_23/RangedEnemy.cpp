#include "pch.h"
#include "RangedEnemy.h"
#include "EnemyProjectile.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "DamageText.h"
#include "PlayerManager.h"
#include "TankEnemy.h"


RangedEnemy::RangedEnemy() :
	_timer(0),
	_attackDelay(10),
	_attackTime(2),
	_damage(1),
	_projectile(nullptr),
	_isHit(false),
	_hitDelay(0.1f),
	_hitTimer(0),
	_isAttack(false)
{

	m_turretTex = GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_1");
	m_turretMaskTex = GET_SINGLE(ResourceManager)->GetTexture(L"EnemyMask");
}

RangedEnemy::~RangedEnemy()
{
	//if (_projectile != nullptr)//여기 고쳐야함
		//GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(_projectile);
}

void RangedEnemy::Update()
{
	Vec2 pos = GetPos();

	if (pos.y >= WINDOW_HEIGHT - 150)
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
		Enemy::Update();
		_timer += fDT;

		if (_isHit)
		{
			_hitTimer += fDT;
			if (_hitDelay <= _hitTimer)
			{

				double normal = GetCurHealth() / GetMaxHealth();

				if (normal <= 0.3f)
				{
					SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"MainTile_3"));
					m_turretTex = (GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_3"));
				}
				else if (normal <= 0.7f)
				{
					SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"MainTile_2"));
					m_turretTex = (GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_2"));
				}
				else
				{
					SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"MainTile"));
					m_turretTex = (GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_1"));
				}

				_hitTimer = 0;
				_isHit = false;
			}
		}


		if (_timer >= _attackTime)
		{
			_attackTime = (rand() % (int)_attackDelay + 2) + ((rand() % 9) / 10.f);
			_timer = 0;
			auto curScene = GET_SINGLE(SceneManager)->GetCurScene();

			auto playerLayerObjects = curScene->GetLayerObjects(Layer::PLAYER);
			if (playerLayerObjects.empty()) return;

			Object* player = GetTarget();
			if (player == nullptr) return;


			EnemyProjectile* proj = new EnemyProjectile;
			Vec2 pos = GetPos();
			pos.y += GetSize().y / 3;
			Vec2 shootDir = this->GetShootDir();
			float angle = shootDir.GetAngleRad({ 0,1 });
			Vec2 newPos = pos.Rotate(angle);
			//pos.y -= GetSize().y / 2.f;
			Vec2 playerPos = player->GetPos();
			proj->SetPos(pos);
			proj->SetSize({ 20.f,20.f });
			proj->Shoot(shootDir * 350);
			proj->SetDamage(_damage);
			curScene->AddObject(proj, Layer::ENEMYPROJECTILE);
			_projectile = proj;

			m_offset = Vec2(0, -10);
		}

		if (m_offset.y < 0)
			m_offset.y += fDT * 20;
		else
		{
			m_offset.y = 0;
		}
	}
}

Vec2 RangedEnemy::GetShootDir()
{
	Vec2 targetPos = GetTarget()->GetPos();
	Vec2 thisPos = GetPos();
	Vec2 dir = { targetPos.x - thisPos.x, targetPos.y - thisPos.y };
	return dir.Normalize();
}

void RangedEnemy::Render(HDC _hdc)
{
	Enemy::Render(_hdc);
	const float lineDistance = 25;
	const float lineWidth = 25;
	Vec2 shootDir = this->GetShootDir();
	float angle = shootDir.GetAngleRad({ 0,1 });
	Vec2 offset = m_offset.Rotate(angle);
	if (shootDir.x > 0)
		offset.x *= -1;
	Vec2 pos = GetPos() + offset;
	Vec2 leftBottom = (pos - shootDir * lineDistance / 1.5f) + shootDir.Rotate(-90) * lineWidth;
	Vec2 leftTop = pos + shootDir * lineDistance * 1.5f + shootDir.Rotate(-90) * lineWidth;
	Vec2 rightTop = pos + shootDir * lineDistance * 1.5f + shootDir.Rotate(90) * lineWidth;

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



void RangedEnemy::SetAttack(double delay, int damage)
{
	_attackDelay = delay;
	_damage = damage;
}



void RangedEnemy::HandleHitEvent(double _prev, double _health)
{
	if (_health <= 0)
	{
		GET_SINGLE(PlayerManager)->AddExp(5);
	}


	double maxHealth = GetMaxHealth();

	double normal = _health / maxHealth;

	if (normal <= 0.3f)
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"MainTile_3"));
		m_turretTex = (GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_3_Hit"));
	}
	else if (normal <= 0.7f)
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"MainTile_2"));
		m_turretTex = (GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_2_Hit"));
	}
	else
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"MainTile"));
		m_turretTex = (GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_1_Hit"));
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
