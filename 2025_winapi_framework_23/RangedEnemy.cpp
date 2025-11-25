#include "pch.h"
#include "RangedEnemy.h"
#include "EnemyProjectile.h"
#include "SceneManager.h"


RangedEnemy::RangedEnemy() : _timer(0), _attackDelay(3), _damage(3), _projectile(nullptr)
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
	cout << (rand() % (int)_attackDelay + 2) + ((rand() % 9) / 10.f) << endl;
	if (_timer >= (rand() % (int)_attackDelay + 2) + ((rand() % 9) / 10.f))
	{
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
		proj->SetDir(playerPos - pos);
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
