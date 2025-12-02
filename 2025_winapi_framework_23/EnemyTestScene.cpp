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
#include "EnchantCard.h"
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
	Spawn<Floor>(Layer::DEFAULT, { 0, WINDOW_HEIGHT / 2}, { 50.f, 1000.f })->GetComponent<Collider>()->SetSize({ 50.f, 1000.f });
	Spawn<Floor>(Layer::DEFAULT, { WINDOW_WIDTH,  WINDOW_HEIGHT / 2 }, { 50.f, 1000.f })->GetComponent<Collider>()->SetSize({ 50.f, 1000.f });

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
		GET_SINGLE(CardManager)->RequestSpawnCards(1);

	if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::NUM_2))
		GET_SINGLE(CardManager)->RequestSpawnCards(2);

	if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::NUM_3))
		GET_SINGLE(CardManager)->RequestSpawnCards(3);

	if (GET_SINGLE(CardManager)->HasSpawnRequest())
	{
		int count = GET_SINGLE(CardManager)->GetSpawnRequest().count;
		GET_SINGLE(CardManager)->ClearSpawnRequest();
		SpawnCards(count);
	}
}

void EnemyTestScene::SpawnCards(int count)
{
	GET_SINGLE(CardManager)->ClearCards();
	Vec2 size = { 200, 300 };
	float spacing = 250;
	float cx = WINDOW_WIDTH / 2;
	float cy = WINDOW_HEIGHT / 2;

	vector<CardInfo> infos = CardDB::GetRandomCard(count);

	auto SpawnOne = [&](Vec2 pos, CardInfo& info)
		{
			EnchantCard* card = Spawn<EnchantCard>(Layer::UI, pos, size);
			card->SetInfo(info.name.c_str(), info.desc.c_str(), info.fileName.c_str());
			GET_SINGLE(CardManager)->AddCard(card);
		};

	if (count == 1)
	{
		SpawnOne({ cx, cy }, infos[0]);
		return;
	}
	if (count == 2)
	{
		SpawnOne({ cx - spacing / 2, cy }, infos[0]);
		SpawnOne({ cx + spacing / 2, cy }, infos[1]);
		return;
	}
	if (count == 3)
	{
		SpawnOne({ cx - spacing, cy }, infos[0]);
		SpawnOne({ cx, cy }, infos[1]);
		SpawnOne({ cx + spacing, cy }, infos[2]);
		return;
	}
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
			if (true)
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
