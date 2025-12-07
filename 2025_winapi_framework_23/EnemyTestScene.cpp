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
#include "CardManager.h"
#include "CardUI.h"
#include "CardDB.h"

void EnemyTestScene::Init()
{
	_enemySpawnTime = 2.5f;
	_timer = 2.5f;
	_enemyCount = 10;
	_spawnPercent = 65;
	//EnemySpawn();

	Spawn<Player>(Layer::PLAYER, { WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 4 }, { 100,100 });
	
	Spawn<Floor>(Layer::DEFAULT, { WINDOW_WIDTH / 2,  0 }, { 1000.f, 50.f });
	Spawn<Floor>(Layer::DEFAULT, { WINDOW_WIDTH / 2, WINDOW_HEIGHT }, { 1000.f, 50.f });
	Spawn<Floor>(Layer::DEFAULT, { 0, WINDOW_HEIGHT / 2}, { 700.f, 1000.f })->GetComponent<Collider>()->SetSize({ 700.f, 1000.f });
	Spawn<Floor>(Layer::DEFAULT, { WINDOW_WIDTH,  WINDOW_HEIGHT / 2 }, { 700.f, 1000.f })->GetComponent<Collider>()->SetSize({ 700.f, 1000.f });

	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMYPROJECTILE);
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
//////////