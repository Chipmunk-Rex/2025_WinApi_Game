#pragma once
#include "BaseCard.h"
#include "Player.h"
#include "LaserProjectile.h"
#include "SceneManager.h"
#include "Scene.h"

class LaserBallCard : public BaseCard
{
protected:
    void OnApply(Player& player) override
    {
        LaserProjectile* laser = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<LaserProjectile>(Layer::PROJECTILE);
        player.AddProjectile(laser);
    }
};
