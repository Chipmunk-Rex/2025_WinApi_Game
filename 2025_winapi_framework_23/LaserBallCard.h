#pragma once
#include "BaseCard.h"
#include "Player.h"
#include "LaserProjectile.h"
#include "SceneManager.h"
#include "Scene.h"

class LaserBallCard : public BaseCard
{
public:
    void Apply(Player& player) override
    {
        LaserProjectile* laser = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<LaserProjectile>(Layer::PROJECTILE, {0,0},{0,50});
        player.AddProjectile(laser);
    }
};
