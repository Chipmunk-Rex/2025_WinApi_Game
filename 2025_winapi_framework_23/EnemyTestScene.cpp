#include "pch.h"
#include "Enemy.h"
#include "Player.h"
#include "EnemyTestScene.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "Floor.h"

void EnemyTestScene::Init()
{
	//Object* obj = new Enemy;
	//obj->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 });
	//obj->SetSize({ 100,100 });
	////obj->SetScene(this);
	//AddObject(obj, Layer::ENEMY);
	cout << "Scene Change" << endl << " : EnemyTestScene";
	


	Spawn<Floor>
		(
			Layer::DEFAULT
			, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 }
	, { 100,100 });

	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
}

void EnemyTestScene::Update()
{
	Scene::Update();
}

void EnemyTestScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}

void EnemyTestScene::EnemySpawn()
{
	Spawn<Enemy>
		(
			Layer::DEFAULT
			, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }
	, { 50,50 });
}
