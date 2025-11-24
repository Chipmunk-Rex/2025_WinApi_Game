#pragma once
#include "Scene.h"
class EnemyTestScene : public Scene
{
public:
	void Init() override;
	void Update() override;
	void Render(HDC _hdc) override;
private:
	double _enemySpawnTime;
	double _timer;
};

