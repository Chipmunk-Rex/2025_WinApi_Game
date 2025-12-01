#pragma once
#include "Projectile.h"
class EnemyProjectile : public Projectile
{
public:
	EnemyProjectile();
	~EnemyProjectile();
public:
    void Update() override;
    void LateUpdate() override;
    void SetDamage(int damage) { _damage = damage; }
    void EnterCollision(Collider* _other) override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;
private:
    Texture* m_pTex;
    int _damage;
    double _timer;
    double _lifeTime;
};

