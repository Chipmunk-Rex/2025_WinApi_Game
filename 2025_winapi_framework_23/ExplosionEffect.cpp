#include "pch.h"
#include "ExplosionEffect.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "SceneManager.h"
#include "Scene.h"
ExplosionEffect::ExplosionEffect()
{
	Texture* animationTex = GET_SINGLE(ResourceManager)->GetTexture(L"Effect_Explosion");
	Animator* animator = AddComponent<Animator>();
	float frameSize = animationTex->GetHeight();
	int frameCount = (animationTex->GetWidth() / frameSize);
	animator->CreateAnimation(L"Explosion", animationTex, Vec2(0.f, 0.f), Vec2(frameSize, frameSize),
		Vec2(frameSize, 0.f), frameCount, 0.05f);
	animator->Play(L"Explosion", PlayMode::Once, 1, 1.0f);
}

ExplosionEffect::~ExplosionEffect()
{
}

void ExplosionEffect::Update()
{
	_timer += fDT;
	if (_timer >= 3.f)
	{
		GET_SINGLE(SceneManager)->LoadScene(L"GameOverScene");;
	}
}

void ExplosionEffect::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}
