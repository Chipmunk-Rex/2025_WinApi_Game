#pragma once
#include "BaseCard.h"
#include "Player.h"

class ProjectileSizeCard : public BaseCard
{
protected:
    void OnApply(Player& player) override
    {
        // 크기 배율 20% 증가
        player.AddProjectileScaleMultiplier(+0.20f);
    }
};
