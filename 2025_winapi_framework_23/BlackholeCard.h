#pragma once
#include "BaseCard.h"
#include "SceneManager.h"
#include "BlockholeProjectile.h"
#include "Scene.h"
class BlackholeCard : public BaseCard
{
	void OnApply(Player& player) override
	{
		BlockholeProjectile* projectile = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<BlockholeProjectile>(Layer::PROJECTILE);
		player.AddProjectile(projectile);
	}
};