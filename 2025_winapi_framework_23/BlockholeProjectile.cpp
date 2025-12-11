#include "pch.h"
#include "BlockholeProjectile.h"
#include "Texture.h"
#include "SceneManager.h"
#include "Scene.h"
#include "BlackHole.h"
#include "PlayerManager.h"
BlockholeProjectile::BlockholeProjectile() : PlayerProjectile()
, _activated(false)
, _duration(5.0f)
, _elapsed(0.0f)
, _damagePerSecond(30)
, _pullStrength(6000.0f)
, _anim(nullptr)
, _ballTex(nullptr)
, _blackholeTex(nullptr)
, _savedVelocity{ 0.f, 0.f }
, _exploding(false)
, explosionDuration(0.8f)
{
	{
		Vec2 defaultSize = { 60.f, 60.f };
		SetDefaultSize(defaultSize);
		SetSize(defaultSize);
	}

	{
		_ballTex = GET_SINGLE(ResourceManager)->GetTexture(L"Projectile_RedGiant_Sheet");
		_blackholeTex = GET_SINGLE(ResourceManager)->GetTexture(L"Projectile_Blackhole_Sheet");
		_ashedTex = GET_SINGLE(ResourceManager)->GetTexture(L"Projectile_Blackhole_Ashed");
		SetTexture(_ashedTex);
	}

	{
		_anim = AddComponent<Animator>();
		float frameDuration = 0.08f;
		Vec2 sliceSize = { (float)_ballTex->GetWidth() / 50.f, (float)_ballTex->GetHeight() };
		Vec2 lt = { 0.f, 0.f };
		Vec2 step = { sliceSize.x, 0.f };
		_anim->CreateAnimation(L"RedGiant", _ballTex, lt, sliceSize, step, 50, frameDuration);
		_anim->CreateAnimation(
			L"Ashed"
			, _ashedTex
			, Vec2{ 0,0 }
			, Vec2{ (float)_ashedTex->GetWidth() , (float)_ashedTex->GetHeight() }
			, Vec2{ 0,0 }
			, 1
			, frameDuration);
		_anim->Play(L"RedGiant", PlayMode::Loop, 1, 1.0f);
	}
}

void BlockholeProjectile::Update()
{
	if (IsActive() == false && _exploding == false)
		return;

	if (_exploding)
	{
		explosionTimer += fDT;
		float t = explosionTimer / explosionDuration;
		if (t > 1.f) t = 1.f;
		float s = ExplosionEase(t);

		Scale({ s, s });
		GetCollider()->SetSize(GetSize() / 2);
		_anim->SetCurrentRenderSize(GetSize());

		if (explosionTimer >= explosionDuration)
		{
			_exploding = false;
			explosionTimer = 0.f;
			_isAshed = true;

			Scene* scene = GET_SINGLE(SceneManager)->GetCurScene();
			BlackHole* bh = scene->RequestSpawn<BlackHole>(Layer::DEFAULT);
			bh->SetPos(GetPos());
			float scaledRatio = GET_SINGLE(PlayerManager)->GetPlayer()->GetProjectileScaleStat().GetValue();
			Vec2 blackholeSize = Vec2{ 200,200 } * scaledRatio;
			bh->SetSize(blackholeSize);
			bh->SetOnFinished([this]() { this->OnBlackholeFinished(); });
		}
	}
	else
	{
		GetCollider()->SetSize(GetSize() / 2);
		_anim->SetCurrentRenderSize(GetSize());
		PlayerProjectile::Update();
	}
}

void BlockholeProjectile::Render(HDC _hdc)
{
	if (IsActive() == false && _exploding == false)
		return;
	ComponentRender(_hdc);
}

void BlockholeProjectile::EnterCollision(Collider* _other)
{
	if (_exploding) return;

	PlayerProjectile::EnterCollision(_other);

	if (_isAshed) return;
	Object* otherOwner = _other ? _other->GetOwner() : nullptr;
	if (!otherOwner || otherOwner->GetLayer() != Layer::ENEMY)
		return;

	_savedVelocity = GetRigidbody()->GetVelocity();
	SetActive(false);
	_exploding = true;
	explosionTimer = 0.f;

	GET_SINGLE(ResourceManager)->Play(L"SFX_RedGiantHit");
}

void BlockholeProjectile::Shoot(Vec2 _dir)
{
	_activated = false;
	_elapsed = 0.f;
	_exploding = false;
	explosionTimer = 0.f;
	_isAshed = false;
	SetTexture(_ballTex);
	SetActive(true);

	_anim->Play(L"RedGiant", PlayMode::Loop, 1, 1.0f);
	if (auto col = GetCollider())
		col->SetSize(GetSize());
	PlayerProjectile::Shoot(_dir);
}


void BlockholeProjectile::OnBlackholeFinished()
{
	SetActive(true);
	SetTexture(_ashedTex);
	SetSize({ 25.f, 25.f });
	_anim->Play(L"Ashed", PlayMode::Loop, 1, 1.0f);
	if (auto col = GetCollider())
		col->SetSize(GetSize());
	if (auto rb = GetRigidbody())
		rb->SetVelocity(_savedVelocity / 5);
	_elapsed = 0.f;
}

void BlockholeProjectile::ActivateBlackhole() {}
void BlockholeProjectile::ApplyAoEDamage() {}
void BlockholeProjectile::AttractNearbyPlayerProjectiles() {}

//thanks AI
float BlockholeProjectile::ExplosionEase(float t) const
{
	// Ease: quick grow to ~1.4x then snap down to small size near end
	// Use an ease-out quad for growth, then blend to a sharp drop
	float grow = 1.0f + 1.8f * (1.0f - (1.0f - t) * (1.0f - t)); // ease-out quad from 1.0 to 1.4
	float dropStart = 0.7f;
	if (t <= dropStart)
		return grow;
	float nt = (t - dropStart) / (1.0f - dropStart); // [0,1]
	float drop = 0.3f + (1.0f - nt) * 0.3f; // quickly towards 0.3
	// Blend grow to drop
	return grow * (1.0f - nt) + drop * nt;
}
