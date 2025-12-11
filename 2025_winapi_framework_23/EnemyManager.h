#pragma once
class EnemyManager
{
	DECLARE_SINGLE(EnemyManager);
public:
	void Init();
	int GetCurrentEnemy();
	void SpawnEnemy();

private:
	int _enemyCount;
	int _currentSpawnCount;
	double _spawnPercent;
};

