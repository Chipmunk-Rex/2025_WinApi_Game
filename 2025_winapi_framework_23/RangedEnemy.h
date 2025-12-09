#pragma once
#include "Enemy.h"
#include "EnemyProjectile.h"
#include "Texture.h"
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
    Vec2 GetShootDir();
private:
    double _timer;
    double _attackDelay;
    double _attackTime;
    double _hitTimer;
    double _hitDelay;
    int _damage;
    bool _isHit;
    Texture* m_turretTex;
    Texture* m_turretMaskTex;
    EnemyProjectile* _projectile;
    Vec2 m_offset;
};

