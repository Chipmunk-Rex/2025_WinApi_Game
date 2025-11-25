#pragma once
#include "Scene.h"
class EnemyTestScene : public Scene
{
public:
	void Init() override;
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void EnemySpawn();
private:
	double _enemySpawnTime;
	double _timer;
	int _enemyCount;
	double _spawnPercent;
};

