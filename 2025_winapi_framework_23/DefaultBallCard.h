#pragma once
#include "BaseCard.h"
#include "Player.h"
#include "PlayerProjectile.h"
#include "SceneManager.h"
#include "Scene.h"

class DefaultBallCard : public BaseCard
{
protected:
    void OnApply(Player& player) override
    {
        PlayerProjectile* laser = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<PlayerProjectile>(Layer::PROJECTILE);
        player.AddProjectile(laser);
    }
};
