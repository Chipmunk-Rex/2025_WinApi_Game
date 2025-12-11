#pragma once
#include "Object.h"
#include "Animator.h"
#include "Texture.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Health.h"
#include "Rigidbody.h"

class BlackHole : public Object
{
public:
    BlackHole();
    ~BlackHole() override;

public:
    void Update() override;
    void Render(HDC _hdc) override;

    void SetDuration(float d) { _duration = d; }
    void SetSize(Vec2 s) override { Object::SetSize(s); _targetSize = s; }
    void SetOnFinished(std::function<void()> cb) { _onFinished = std::move(cb); }

private:
    void ApplyDamageToRegion();
    void AttractNearbyPlayerProjectiles();
    float SpawnEase(float t) const; // easing for initial growth
    float DespawnEase(float t) const; // easing for shrink when disappearing

private:
    float _duration;
    float _elapsed;
    Vec2 _aoeSize;
    int _damage;
    float _pullStrength;

	float _damageTimer;

    bool _spawning;
    float _spawnDuration;
    float _spawnTimer;
    Vec2 _targetSize;
    Vec2 _aoeBaseSize;

    bool _despawning;
    float _despawnDuration;
    float _despawnTimer;

    Animator* _anim;
    Texture* _tex;
    std::function<void()> _onFinished;
};
