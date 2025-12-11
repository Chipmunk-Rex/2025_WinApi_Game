#pragma once
#include "PlayerProjectile.h"
#include "Animator.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Health.h"
#include "Rigidbody.h"
#include "Texture.h"

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
    const Texture* GetIconTexture() { return _blackholeIconTex; };
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
    Texture* _blackholeIconTex;
    Texture* _ashedTex;

	bool _isAshed = false;
};

