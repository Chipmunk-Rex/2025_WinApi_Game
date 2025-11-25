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
private:
    double _timer;
    double _attackDelay;
    int _damage;
    EnemyProjectile* _projectile;
};

