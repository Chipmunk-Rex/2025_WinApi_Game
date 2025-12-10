#pragma once
#include "Projectile.h"
class BounceEnemyProjectile : public Projectile
{
public:
    BounceEnemyProjectile();
    ~BounceEnemyProjectile();
public:
    void Update() override;
    void Render(HDC _hdc) override;
    void LateUpdate() override;
    void EnterCollision(Collider* _other) override;
    void SetDamage(int damage) { _damage = damage; }
private:
    double _damage;
    int m_count;
};

