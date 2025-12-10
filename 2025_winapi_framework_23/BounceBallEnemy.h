#pragma once
#include "Enemy.h"
#include "EnemyProjectile.h"
#include "BounceEnemyProjectile.h"
class BounceBallEnemy : public Enemy
{
public:
	BounceBallEnemy();
	~BounceBallEnemy();
public:
	void Update() override;
	// Object을(를) 통해 상속됨'
	void Render(HDC _hdc) override;
	void HandleHitEvent(double _prev, double _health) override;
    Vec2 GetShootDir();
    void Aattack();
private:
    double _timer;
    double _attackDelay;
    double _attackTime;
    double _hitTimer;
    double _hitDelay;
    int _damage;
    bool _isHit;
    bool _isAttack;
    bool _isAttacking;
    BounceEnemyProjectile* _projectile;

};

