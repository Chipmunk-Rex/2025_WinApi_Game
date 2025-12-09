#pragma once
#include "BaseCard.h"
#include "Player.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SlowProjectile.h"
#include "pch.h"
class SlowBallCard : public BaseCard
{
	void OnApply(Player& player) override
	{

		SlowProjectile* projectile = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<SlowProjectile>(Layer::PROJECTILE);
		player.AddProjectile(projectile);
	}
};