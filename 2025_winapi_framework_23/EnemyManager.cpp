#include "pch.h"
#include "EnemyManager.h"
#include "CloseRangeEnemy.h"
#include "RangedEnemy.h"
#include "BounceBallEnemy.h"
#include "DownAttackEnemy.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TankEnemy.h"

void EnemyManager::Init()
{
	_enemyCount = 10;
	_currentSpawnCount = 0;
	_spawnPercent = 65;
}

int EnemyManager::GetCurrentEnemy()
{
	Scene* curScene = GET_SINGLE(SceneManager)->GetCurScene();
	int count = curScene->GetLayerObjects(Layer::ENEMY).size();
	return count;
}

void EnemyManager::SpawnEnemy()
{
	Scene* curScene = GET_SINGLE(SceneManager)->GetCurScene();

	bool isBeginning = (_currentSpawnCount / _enemyCount) < 8;

	for (int i = 0; i < _enemyCount; i++)
	{
		if (rand() % 100 <= _spawnPercent)
		{
			float randValue = rand() % 100;
			if (randValue < 65)//
			{
				CloseRangeEnemy* enemy = curScene->Spawn<CloseRangeEnemy>
					(
						Layer::ENEMY
						, { (WINDOW_WIDTH / 2 - (50 * (_enemyCount / 2))) + (50 * i) + 25,  -100 }
				, { 50,50 });
				float mulValue = ((_currentSpawnCount / _enemyCount) + 1) * 0.2f;
				enemy->SetHealth(10 * mulValue);
			}
			else if (!isBeginning && randValue < 70)
			{
				RangedEnemy* enemy = curScene->Spawn<RangedEnemy>
					(
						Layer::ENEMY
						, { (WINDOW_WIDTH / 2 - (50 * (_enemyCount / 2))) + (50 * i) + 25, -100 }
				, { 50,50 });
				float mulValue = ((_currentSpawnCount / _enemyCount) + 1) * 0.2f;
				enemy->SetHealth(10 * mulValue);
			}
			else if (!isBeginning && randValue < 80)
			{
				BounceBallEnemy* enemy = curScene->Spawn<BounceBallEnemy>
					(
						Layer::ENEMY
						, { (WINDOW_WIDTH / 2 - (50 * (_enemyCount / 2))) + (50 * i) + 25, -100 }
				, { 50,50 });
				float mulValue = ((_currentSpawnCount / _enemyCount) + 1) * 0.2f;
				enemy->SetHealth(10 * mulValue);

			}
			else if (randValue < 90)
			{
				DownAttackEnemy* enemy = curScene->Spawn<DownAttackEnemy>
					(
						Layer::ENEMY
						, { (WINDOW_WIDTH / 2 - (50 * (_enemyCount / 2))) + (50 * i) + 25, -100 }
				, { 50,50 });
				float mulValue = ((_currentSpawnCount / _enemyCount) + 1) * 0.2f;
				enemy->SetHealth(10 * mulValue);
			}
			else if (!(i + 1 == _enemyCount) && !isBeginning)
			{
				TankEnemy* enemy = curScene->Spawn<TankEnemy>
					(
						Layer::ENEMY
						, { ((WINDOW_WIDTH / 2 - (50 * (_enemyCount / 2))) + (50 * i)) + 50, -100 }
				, { 100,50 });
				float mulValue = ((_currentSpawnCount / _enemyCount) + 1) * 0.2f;
				enemy->SetHealth((10 * mulValue) * 3);
				++i;
			}

			_currentSpawnCount++;
		}
	}
}
