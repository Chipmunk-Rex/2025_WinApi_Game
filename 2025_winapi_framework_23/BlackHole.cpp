#include "pch.h"
#include "BlackHole.h"
#include "Projectile.h"

BlackHole::BlackHole()
    : _duration(5.0f)
    , _elapsed(0.0f)
    , _aoeSize{ 180.f, 180.f }
    , _damage(5)
    , _pullStrength(6000.0f)
    , _spawning(true)
    , _spawnDuration(0.35f)
    , _spawnTimer(0.0f)
    , _targetSize{ 180.f, 180.f }
    , _aoeBaseSize{ 180.f, 180.f }
    , _despawning(false)
    , _despawnDuration(0.2f)
    , _despawnTimer(0.0f)
    , _anim(nullptr)
    , _tex(nullptr)
    , _damageTimer(0) 
{
    SetActive(true);
    _anim = AddComponent<Animator>();
    _tex = GET_SINGLE(ResourceManager)->GetTexture(L"Projectile_Blackhole_Sheet");
    if (_tex && _anim)
    {
        float frameDuration = 0.08f;
        Vec2 sliceSize = { (float)_tex->GetWidth() / 50.f, (float)_tex->GetHeight() };
        Vec2 lt = { 0.f, 0.f };
        Vec2 step = { sliceSize.x, 0.f };
        _anim->CreateAnimation(L"Blackhole", _tex, lt, sliceSize, step, 50, frameDuration);
        _anim->Play(L"Blackhole", PlayMode::Loop, 1, 1.0f);
    }
    Object::SetSize({ 10.f, 10.f });
    _aoeSize = { 10.f, 10.f };


    GET_SINGLE(ResourceManager)->Play(L"SFX_BlackholeSpawn");
}

BlackHole::~BlackHole() {}

void BlackHole::Update()
{
    if (_despawning)
    {
        _despawnTimer += fDT;
        float t = _despawnTimer / _despawnDuration; if (t > 1.f) t = 1.f;
        float s = DespawnEase(t); 
        Vec2 size = _targetSize * s;
        Object::SetSize(size);
        _aoeSize = _aoeBaseSize * s;
        if (_anim)
            _anim->SetCurrentRenderSize(size);
        if (_despawnTimer >= _despawnDuration)
        {
            if (_onFinished)
                _onFinished();

            GET_SINGLE(SceneManager)->RequestDestroy(this);
        }
        return;
    }

    _elapsed += fDT;

    if (_spawning)
    {
        _spawnTimer += fDT;
        float t = _spawnTimer / _spawnDuration; if (t > 1.f) t = 1.f;
        float s = SpawnEase(t); 
        Vec2 size = _targetSize * s;
        Object::SetSize(size);
        _aoeSize = _aoeBaseSize * s;
        if (_anim)
            _anim->SetCurrentRenderSize(size);
        if (_spawnTimer >= _spawnDuration)
        {
            _spawning = false;
            Object::SetSize(_targetSize);
            _aoeSize = _aoeBaseSize;
            if (_anim)
                _anim->SetCurrentRenderSize(_targetSize);
        }
    }

	static float damageCooldown = 0.1f;
    _damageTimer += fDT;
    if (_damageTimer >= damageCooldown)
    {
        ApplyDamageToRegion();
        _damageTimer -= damageCooldown;
    }

    AttractNearbyPlayerProjectiles();
    if (_elapsed >= _duration)
    {
        _despawning = true;
        GET_SINGLE(ResourceManager)->Play(L"SFX_BlackholeDestroy");
        _despawnTimer = 0.0f;
        return;
    }
}

void BlackHole::Render(HDC _hdc)
{
    if (_anim && _anim->GetCurrent())
        _anim->Render(_hdc);
}

void BlackHole::ApplyDamageToRegion()
{
    std::vector<Collider*> hits;
    Vec2 origin = GetPos();
    GET_SINGLE(CollisionManager)->OverlapBox(origin, _aoeSize, LayerToMask(Layer::ENEMY), hits);
    for (Collider* c : hits)
    {
        if (!c) continue;
        Object* o = c->GetOwner();
        if (!o) continue;
        Health* h = o->GetComponent<Health>();
        if (h)
        {
            h->TakeDamage((double)_damage);
        }
    }
}

void BlackHole::AttractNearbyPlayerProjectiles()
{
    std::vector<Collider*> hits;
    Vec2 origin = GetPos();
    GET_SINGLE(CollisionManager)->OverlapBox(origin, _aoeSize, LayerToMask(Layer::PROJECTILE), hits);
    for (Collider* c : hits)
    {
        if (!c) continue;
        Object* o = c->GetOwner();
        if (!o) continue;
        Projectile* pp = dynamic_cast<Projectile*>(o);
        if (!pp) continue;
        Rigidbody* rb = o->GetComponent<Rigidbody>();
        if (!rb) continue;
        Vec2 dir = origin - o->GetPos();
        float len = dir.Length();
        if (len < FLT_EPSILON) continue;
        dir = dir.Normalize();
        Vec2 vel = rb->GetVelocity();
        vel = vel + dir * (_pullStrength * fDT);
        rb->SetVelocity(vel);
    }
}

float BlackHole::SpawnEase(float t) const
{
    // Ease-out quad
    return 1.0f - (1.0f - t) * (1.0f - t);
}

float BlackHole::DespawnEase(float t) const
{
    // Ease-in quad 
    float s = t * t; // 0->1
    return 1.0f - s; // 1->0
}
