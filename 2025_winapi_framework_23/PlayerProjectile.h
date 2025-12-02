#pragma once
#include "Projectile.h"
class PlayerProjectile : public Projectile
{
public:
    PlayerProjectile();
    ~PlayerProjectile() override;
public:
    void Update() override;
    void Render(HDC _hdc) override;
    void EnterCollision(Collider* _other) override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;
public:
    void Shoot(Vec2 _dir) override;
    void SetDamage(int damage) { _damage = damage; }
	bool CanCollect() const { return shootTimer >= 1.f; }
private:
    int _damage;
	float shootTimer = 0.f;
};

