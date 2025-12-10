#pragma once
#include "PlayerProjectile.h"
#include "Animator.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Health.h"
#include "Rigidbody.h"
#include "Texture.h"

// Blackhole projectile: starts as a black ball; upon colliding with an enemy, activates
// into a blackhole that plays an animation and applies AoE damage while attracting
// nearby player projectiles.
class BlockholeProjectile : public PlayerProjectile
{
public:
    BlockholeProjectile();
    ~BlockholeProjectile() override {}

public:
    void Update() override;
    void Render(HDC _hdc) override;
    void EnterCollision(Collider* _other) override;
    void StayCollision(Collider* _other) override {}
    void ExitCollision(Collider* _other) override {}
    void Shoot(Vec2 _dir) override;


    void OnBlackholeFinished();

private:
    void ActivateBlackhole();
    void ApplyAoEDamage();
    void AttractNearbyPlayerProjectiles();

    float ExplosionEase(float t) const;

private:
    bool _activated;
    float _duration;
    float _elapsed;
    int _damagePerSecond;
    float _pullStrength;
    Vec2 _savedVelocity; 

    bool _exploding;
    float explosionDuration;
    float explosionTimer = 0;

    Animator* _anim;
    Texture* _ballTex;
    Texture* _blackholeTex;
    Texture* _ashedTex;

	bool _isAshed = false;
};

