#include "pch.h"
#include "Enemy.h"
#include "Player.h"
#include "EnemyTestScene.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "Floor.h"
#include "CloseRangeEnemy.h"
#include "RangedEnemy.h"
#include "Health.h"

void EnemyTestScene::Init()
{
	_enemySpawnTime = 2.5f;
	_timer = 2.5f;
	_enemyCount = 10;
	_spawnPercent = 65;
	//EnemySpawn();

	Spawn<Player>(Layer::PLAYER, { WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 4 }, { 50,50 });

	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMYPROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMYPROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
}

void EnemyTestScene::Update()
{
	Scene::Update();
	_timer += fDT;
	if (_timer >= _enemySpawnTime)
	{
		_timer = 0;
		EnemySpawn();
	}

	/*for (auto obj : GetLayerObjects(Layer::ENEMY))
	{
		if (obj->GetComponent<Health>() != nullptr)
		{
			if (obj->GetComponent<Health>()->GetIsDead())
			{
				RequestDestroy(obj);
			}
		}
	}*/
}

void EnemyTestScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}

void EnemyTestScene::EnemySpawn()
{
	for (int i = 0; i < _enemyCount; i++)
	{
		if (rand() % 100 <= _spawnPercent)
		{
			if (rand() % 100 <= 50)
			{
				Spawn<CloseRangeEnemy>
					(
						Layer::ENEMY
						, { (WINDOW_WIDTH / 2 - (50 * (_enemyCount / 2))) + (50 * i),  -100 }
				, { 50,50 });
			}
			else
			{
				Spawn<RangedEnemy>
					(
						Layer::ENEMY
						, { (WINDOW_WIDTH / 2 - (50 * (_enemyCount / 2))) + (50 * i), -100 }
				, { 50,50 });
			}
		}
	}
}
