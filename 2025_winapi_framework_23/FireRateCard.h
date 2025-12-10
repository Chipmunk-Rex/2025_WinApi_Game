#pragma once
#include "BaseCard.h"
#include "Player.h"

class FireRateCard : public BaseCard
{
protected:
    void OnApply(Player& player) override
    {
        player.AddFireCooldownMultiplier(-0.10f);
    }
};
