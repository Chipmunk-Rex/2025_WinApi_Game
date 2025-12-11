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
#include "Collider.h"
#include "InputManager.h"
#include "PlayerManager.h"
#include "CardManager.h"
#include "CardUI.h"
#include "CardDB.h"
#include "PlayerInfoUI.h"
#include "Background.h"
#include "TankEnemy.h"
#include "BounceBallEnemy.h"
#include "DownAttackEnemy.h"
#include "GameFasterButton.h"

void EnemyTestScene::Init()
{
	_enemySpawnTime = 5.f;
	_timer = 5.f;
	_enemyCount = 10;
	_currentSpawnCount = 0;
	_spawnPercent = 65;
	//EnemySpawn();

	SET_TIME_SCALE(1);

	// Spawn background first
	Spawn<Background>(Layer::BACKGROUND, { WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 }, { WINDOW_WIDTH, WINDOW_HEIGHT });

	Spawn<Player>(Layer::PLAYER);
	{
		{
			const float wallThickness = 100;
			const float wallLength = (float)WINDOW_WIDTH;
			Spawn<Floor>(Layer::DEFAULT, { (float)WINDOW_WIDTH / 2,  0 - (wallThickness / 2) }, {})
				->SetSize({ wallLength, wallThickness });
			Spawn<Floor>(Layer::DEFAULT, { (float)WINDOW_WIDTH / 2, WINDOW_HEIGHT + (wallThickness / 2) }, {})
				->SetSize({ wallLength, wallThickness });
		}
		{
			const float wallLength = (float)WINDOW_HEIGHT;
			float yCenter = WINDOW_HEIGHT / 2;
			Spawn<Floor>(Layer::DEFAULT, { 0.f,  yCenter }, {})
				->SetSize({ 775.f, wallLength });
			Spawn<Floor>(Layer::DEFAULT, { (float)WINDOW_WIDTH,  yCenter }, {})
				->SetSize({ 775.f, wallLength });
		}
	}
	Spawn<PlayerInfoUI>(Layer::UI, { WINDOW_WIDTH / 2,  0 }, { 1000.f, 50.f });
	Spawn<GameFasterButton>(Layer::UI, { 1070,75 }, { 45, 35 })->SetSpeed(L"1", 1);
	Spawn<GameFasterButton>(Layer::UI, { 1140,75 }, { 45, 35 })->SetSpeed(L"2", 2);
	Spawn<GameFasterButton>(Layer::UI, { 1210,75 }, { 45, 35 })->SetSpeed(L"3", 3);

	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::BOUNCEPROJECTILE, Layer::DEFAULT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::BOUNCEPROJECTILE, Layer::PLAYER);
	//GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMYPROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::DEFAULT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMYPROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
}






void EnemyTestScene::Update()
{
	Scene::Update();

	GET_SINGLE(CardManager)->Update();

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


	if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::NUM_1))
		GET_SINGLE(CardManager)->SpawnCards(1);

	if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::NUM_2))
		GET_SINGLE(CardManager)->SpawnCards(2);

	if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::NUM_3))
		GET_SINGLE(CardManager)->SpawnCards(3);

	if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::E))
		GET_SINGLE(PlayerManager)->AddExp(100);
}

void EnemyTestScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}

void EnemyTestScene::EnemySpawn()
{
	srand(time(nullptr));

	for (int i = 0; i < _enemyCount; i++)
	{
		if (rand() % 100 <= _spawnPercent)
		{
			float randValue = rand() % 100;
			if (randValue < 55)//
			{
				CloseRangeEnemy* enemy = Spawn<CloseRangeEnemy>
					(
						Layer::ENEMY
						, { (WINDOW_WIDTH / 2 - (50 * (_enemyCount / 2))) + (50 * i) + 25,  -100 }
				, { 50,50 });
				float mulValue = ((_currentSpawnCount / _enemyCount) + 1) * 0.2f;
				enemy->SetHealth(10 * mulValue);
			}
			else if (randValue < 60)
			{
				RangedEnemy* enemy = Spawn<RangedEnemy>
					(
						Layer::ENEMY
						, { (WINDOW_WIDTH / 2 - (50 * (_enemyCount / 2))) + (50 * i) + 25, -100 }
				, { 50,50 });
				float mulValue = ((_currentSpawnCount / _enemyCount) + 1) * 0.2f;
				enemy->SetHealth(10 * mulValue);
			}
			else if (randValue < 65)
			{
				BounceBallEnemy* enemy = Spawn<BounceBallEnemy>
					(
						Layer::ENEMY
						, { (WINDOW_WIDTH / 2 - (50 * (_enemyCount / 2))) + (50 * i) + 25, -100 }
				, { 50,50 });
				float mulValue = ((_currentSpawnCount / _enemyCount) + 1) * 0.2f;
				enemy->SetHealth(10 * mulValue);

			}
			else if (randValue < 90)
			{
				DownAttackEnemy* enemy = Spawn<DownAttackEnemy>
					(
						Layer::ENEMY
						, { (WINDOW_WIDTH / 2 - (50 * (_enemyCount / 2))) + (50 * i), -100 }
				, { 50,50 });
				float mulValue = ((_currentSpawnCount / _enemyCount) + 1) * 0.2f;
				enemy->SetHealth(10 * mulValue);
			}
			else if (!(i + 1 == _enemyCount))
			{
				TankEnemy* enemy = Spawn<TankEnemy>
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
}//////////