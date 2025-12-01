#pragma once
#include "Enemy.h"
#include "EnemyProjectile.h"
class RangedEnemy : public Enemy
{
public:
    RangedEnemy();
    ~RangedEnemy();
public:
    void Update() override;
    // Object을(를) 통해 상속됨'
    void Render(HDC _hdc) override;
    void SetAttack(double delay, int damage);
    void HandleHitEvent(double _prev, double _health) override;
private:
    double _timer;
    double _attackDelay;
    double _attackTime;
    int _damage;
    EnemyProjectile* _projectile;
};

