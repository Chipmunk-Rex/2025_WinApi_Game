#include "pch.h"
#include "RangedEnemy.h"
#include "EnemyProjectile.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "DamageText.h"


RangedEnemy::RangedEnemy() : _timer(0), _attackDelay(10), _attackTime(2), _damage(3), _projectile(nullptr)
{
}

RangedEnemy::~RangedEnemy()
{
	if(_projectile != nullptr)//여기 고쳐야함
	GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(_projectile);
}

void RangedEnemy::Update()
{
	Enemy::Update();
	_timer += fDT;
	if (_timer >= _attackTime)
	{
		_attackTime = (rand() % (int)_attackDelay + 2) + ((rand() % 9) / 10.f);
		_timer = 0;
		auto curScene = GET_SINGLE(SceneManager)->GetCurScene();
		
		auto playerLayerObjects = curScene->GetLayerObjects(Layer::PLAYER);
		if (playerLayerObjects.empty()) return;

		Object* player = curScene->GetLayerObjects(Layer::PLAYER)[0];
		EnemyProjectile* proj = new EnemyProjectile;
		Vec2 pos = GetPos();
		pos.y += GetSize().y / 2;
		//pos.y -= GetSize().y / 2.f;
		Vec2 playerPos = player->GetPos();
		proj->SetPos(pos);
		proj->SetSize({ 20.f,20.f });
		proj->Shoot(playerPos - pos);
		proj->SetDamage(_damage);
		curScene->AddObject(proj,Layer::ENEMYPROJECTILE);
		_projectile = proj;
	}
}

void RangedEnemy::Render(HDC _hdc)
{
	Enemy::Render(_hdc);
}

void RangedEnemy::SetAttack(double delay, int damage)
{
	_attackDelay = delay;
	_damage = damage;
}

void RangedEnemy::HandleHitEvent(double _prev, double _health)
{
	double maxHealth = GetMaxHealth();

	double normal = _health / maxHealth;

	if (normal <= 0.3f)
	{
		SetTex(GET_SINGLE(ResourceManager)->GetTexture(L"Red_Brick_3"));
	}
	else if(normal <= 0.7f)
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
